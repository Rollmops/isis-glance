/****************************************************************
 *
 * <Copyright information>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 3
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 *
 * Author: Erik Tuerke, etuerke@googlemail.com
 *
 * qt_widget.cpp
 *
 * Description:
 *
 *  Created on: Jun 27, 2012
 *      Author: tuerke
 ******************************************************************/
#include "qt_widget.hpp"
#include <qt4/QtGui/QPainter>
#include <DataStorage/io_factory.hpp>

namespace isis
{
namespace glance
{
namespace widget
{

QtWidget::QtWidget ( QWidget *parent )
	: Qt4WidgetBase ( parent ),
	rasteringFactor_(100)
{
	setAutoFillBackground( true );
	setPalette( QPalette( Qt::black ) );
	connectSignals();
}

void QtWidget::connectSignals()
{

}

void QtWidget::updateViewPort()
{
	//update viewport
	boundingBox_.refresh(*this);
	window_ = boundingBox_.asMappedExtentType(plane_orientation) * rasteringFactor_ ;
	const float _width = window_[2] / rasteringFactor_;
	const float _height = window_[3] / rasteringFactor_;

	const float scalew = width() / _width;
	const float scaleh = height() / _height;

	windowViewPortScaling_ = std::min( scaleh, scalew );
	const float offsetW = ( width() - ( _width * windowViewPortScaling_ ) ) / 2. ;
	const float offsetH = ( height() - ( _height * windowViewPortScaling_ ) ) / 2.;
	viewPort_ = isis::util::fvector4( 	offsetW,
									offsetH,
									( _width * windowViewPortScaling_ ),
									( _height * windowViewPortScaling_ ) );
}


void QtWidget::paintEvent ( QPaintEvent * )
{
	QPainter painter(this );
	painter.resetTransform();

	updateViewPort();
	painter.setWindow( window_[0], window_[1], window_[2], window_[3] );
	painter.setViewport( viewPort_[0], viewPort_[1], viewPort_[2], viewPort_[3] );
	paintImage(getVector().front(), painter);

	
	painter.end();
}


void QtWidget::paintImage ( const glance::data::Image::SharedPointer &image, QPainter &painter )
{
	painter.setTransform( getTransform2ISISSpace() );
	painter.setTransform( getQtransform(image), true );
	painter.setOpacity(image->opacitiy);

	const isis::glance::data::Volume::ivec coords( image->voxel_coords[0], image->voxel_coords[1], image->voxel_coords[2] );
	
	isis::glance::data::Slice slice = image->operator[](image->current_volume).extractSlice(
			isis::glance::geometrical::getMatrixForPlaneOrientation( plane_orientation ),
			coords, true );

	QImage qImage( static_cast<glance::data::types::ScalarRepnProposed*>( slice->getRawAddress().get() ),
					slice.getSizeAsVector()[0], slice.getSizeAsVector()[1],
					QImage::Format_Indexed8 );
	
	QVector<QRgb>ct(256);
	for( unsigned short i = 0; i < 256; ++i ) {
		ct[i] = QColor( i,i,i ).rgb();
	}
	qImage.setColorTable(ct);

	painter.drawImage(0,0,qImage);
}

isis::util::Matrix3x3< qreal > QtWidget::getOrderedMatrix( const isis::glance::data::Image::SharedPointer &image) const
{
	const bool inverse = false; //TODO
	const bool latched = false; //TODO
	isis::util::Matrix3x3<qreal> latchedOrientation_abs;

	for( unsigned short i = 0; i < 3; i++ ) {
		for( unsigned short j = 0; j < 3; j++ ) {
			latchedOrientation_abs.elem( i, j ) = fabs( image->orientation_matrix_latched.elem( i, j ) );
		}
	}

	isis::util::Matrix3x3<qreal> invLatchedOrientation;
	bool invOk;

	if( inverse ) {
		invLatchedOrientation = latchedOrientation_abs.inverse( invOk );

		if( !invOk ) {
			LOG( isis::glance::data::Runtime, warning ) << "Failed to use inverse to extract 2D matrix for image " << image->file_path
								<< "! Falling back to transposed.";
		}
	}

	if( !inverse || !invOk ) {
		invLatchedOrientation = latchedOrientation_abs.transpose();
	}

	const isis::util::Matrix3x3<qreal> mat = latched ? image->orientation_matrix_latched.dot( invLatchedOrientation )
		: image->orientation_matrix.dot( invLatchedOrientation );

	return mat;
}


isis::util::FixedMatrix< qreal, 2, 2 > QtWidget::extract2DMatrix( const isis::glance::data::Image::SharedPointer &image) const
{
	const isis::util::Matrix3x3<qreal> mat = getOrderedMatrix( image );
	isis::util::FixedMatrix<qreal, 2, 2> retMatrix;

	switch( plane_orientation ) {
	case geometrical::AXIAL:
		retMatrix.elem( 0, 0 ) = mat.elem( 0, 0 );
		retMatrix.elem( 0, 1 ) = mat.elem( 0, 1 );
		retMatrix.elem( 1, 0 ) = mat.elem( 1, 0 );
		retMatrix.elem( 1, 1 ) = mat.elem( 1, 1 );
		break;
	case geometrical::SAGITTAL:
		retMatrix.elem( 0, 0 ) = mat.elem( 1, 1 );
		retMatrix.elem( 1, 0 ) = mat.elem( 2, 1 );
		retMatrix.elem( 0, 1 ) = mat.elem( 1, 2 );
		retMatrix.elem( 1, 1 ) = mat.elem( 2, 2 );
		break;
	case geometrical::CORONAL:
		retMatrix.elem( 0, 0 ) = mat.elem( 0, 0 );
		retMatrix.elem( 1, 0 ) = mat.elem( 2, 0 );
		retMatrix.elem( 0, 1 ) = mat.elem( 0, 2 );
		retMatrix.elem( 1, 1 ) = mat.elem( 2, 2 );
		break;
	case geometrical::NOT_SPECIFIED:
		break;
	}

	return retMatrix;
}


QTransform QtWidget::getQtransform( const isis::glance::data::Image::SharedPointer &image) const
{
	const isis::util::FixedMatrix<qreal, 2, 2> mat = extract2DMatrix( image );

	isis::util::fvector3 mapped_voxelSize = geometrical::mapCoordsToOrientation( image->voxel_size, image->orientation_matrix_latched, plane_orientation, false, true ) * rasteringFactor_;

	const uint16_t slice = geometrical::mapCoordsToOrientation( image->voxel_coords, image->orientation_matrix_latched, plane_orientation, false, true )[2];
	const isis::util::ivector4 mappedCoords = geometrical::mapCoordsToOrientation( isis::util::ivector4( 0, 0, slice ), image->orientation_matrix_latched, plane_orientation, true, true );
	const isis::util::fvector3 _io = image->get().getPhysicalCoordsFromIndex( mappedCoords ) * rasteringFactor_ ;
	isis::util::FixedVector<qreal, 2> vc;
	vc[0] = mapped_voxelSize[0] / 2.0;
	vc[1] = mapped_voxelSize[1] / 2.0;
	const isis::util::FixedVector<qreal, 2> _vc = mat.dot( vc );


	switch( plane_orientation ) {
	case geometrical::AXIAL: {
		QTransform tr1;
		return QTransform( QTransform( mat.elem( 0, 0 ), mat.elem( 0, 1 ), mat.elem( 1, 0 ), mat.elem( 1, 1 ), 0, 0 )
						   * tr1.translate( _io[0] - _vc[0], _io[1] - _vc[1] ) ).scale( mapped_voxelSize[0], mapped_voxelSize[1] );
		break;
	}
	case geometrical::SAGITTAL: {
		QTransform tr1;
		return QTransform( QTransform( mat.elem( 0, 0 ), mat.elem( 0, 1 ), mat.elem( 1, 0 ), mat.elem( 1, 1 ), 0, 0 )
						   * tr1.translate( _io[1] - _vc[0], _io[2] - _vc[1] ) ).scale( mapped_voxelSize[0], mapped_voxelSize[1] );
		break;
	}
	case geometrical::CORONAL: {
		QTransform tr1;
		return QTransform( QTransform( mat.elem( 0, 0 ), mat.elem( 0, 1 ), mat.elem( 1, 0 ), mat.elem( 1, 1 ), 0, 0 )
						   * tr1.translate( _io[0] - _vc[0], _io[2] - _vc[1] ) ).scale( mapped_voxelSize[0], mapped_voxelSize[1] );
		break;
	}
	case geometrical::NOT_SPECIFIED:
		break;
	}

	return QTransform();
}




QTransform QtWidget::getTransform2ISISSpace() const
{
	QTransform retTransform;

	switch ( plane_orientation ) {
	case geometrical::AXIAL:
		retTransform = QTransform( -1, 0, 0, 1, window_[2] + ( window_[0] * 2 ), 0 );
		break;
	case geometrical::SAGITTAL:
		retTransform = QTransform( 1, 0, 0, -1, 0, window_[3] + ( window_[1] * 2 ) );
		break;
	case geometrical::CORONAL:
		retTransform = QTransform( -1, 0, 0, -1, window_[2] + ( window_[0] * 2 ), window_[3] + ( window_[1] * 2 ) );
		break;
	case geometrical::NOT_SPECIFIED:
		break;
	}
	return retTransform;
}

void QtWidget::zoomWindow()
{
	const isis::util::fvector4 oldWindow = window_;
}


// void zoomBoundingBox ( util::fvector4 &boundingBox, util::FixedVector<float, 2> &translation, const util::fvector3 &physCoord, const float &zoom, const PlaneOrientation &orientation, const bool &translate )
// {
// 	const util::fvector4 oldBoundingBox = boundingBox;
// 
// 	if( translate ) {
// 		const float centerX = boundingBox[0] + ( boundingBox[2] / 2. );
// 		const float centerY = boundingBox[1] + ( boundingBox[3] / 2. );
// 
// 		const util::fvector3 mappedPhysicalCoords = mapPhysicalCoords2Orientation( physCoord, orientation ) * rasteringFac;
// 		const float diffX = ( ( centerX - mappedPhysicalCoords[0] ) / ( boundingBox[2] / 2. ) );
// 		const float diffY = ( ( centerY - mappedPhysicalCoords[1] ) / ( boundingBox[3] / 2. ) );
// 		translation[0] = diffX * ( ( boundingBox[2] - ( boundingBox[2] / zoom * 0.9 ) ) / 2. );
// 		translation[1] = diffY * ( ( boundingBox[3] - ( boundingBox[3] / zoom * 0.9 ) ) / 2. );
// 	}
// 
// 	boundingBox[2] /= zoom;
// 	boundingBox[3] /= zoom;
// 	//translate bounding box
// 	boundingBox[0] += ( oldBoundingBox[2] - boundingBox[2] ) / 2.;
// 	boundingBox[1] += ( oldBoundingBox[3] - boundingBox[3] ) / 2.;
// }

} // end namespace widget
} // end namespace glance
} // end namespace isis
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
 * qt_widget.hpp
 *
 * Description:
 *
 *  Created on: Jun 27, 2012
 *      Author: tuerke
 ******************************************************************/
#ifndef _ISIS_GLANCE_WIDGET_PLUGIN_QT_HPP
#define _ISIS_GLANCE_WIDGET_PLUGIN_QT_HPP

#include <qt4_widget_base.hpp>
#include <QWidget>
#include "data/bounding_box.hpp"

namespace isis
{
namespace glance
{
namespace widget
{


class QtWidget : public qt4::_internal::Qt4WidgetBase
{
public:
	QtWidget( QWidget *parent = 0 );

public Q_SLOTS:
	void paintEvent( QPaintEvent * );
private:
	void connectSignals();
	void paintImage( const isis::glance::data::Image::SharedPointer &image, QPainter &painter );

	void updateViewPort();

	QTransform getTransform2ISISSpace() const;
	void zoomWindow();
	QTransform getQtransform( const isis::glance::data::Image::SharedPointer &image ) const;
	isis::util::Matrix3x3< qreal > getOrderedMatrix( const isis::glance::data::Image::SharedPointer &image ) const;
	isis::util::FixedMatrix<qreal, 2, 2> extract2DMatrix( const isis::glance::data::Image::SharedPointer &image ) const;

	isis::glance::data::BoundingBox boundingBox_;
	isis::glance::data::BoundingBox::MappedExtentType window_;
	isis::util::fvector4 viewPort_;
	float windowViewPortScaling_;
	uint16_t rasteringFactor_;

};

} // end namespace widget
} // end namespace glance
} // end namespace isis

#endif // _ISIS_GLANCE_WIDGET_PLUGIN_QT_HPP
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
 * geometrical.cpp
 *
 * Description:
 *
 *  Created on: Jun 8, 2012
 *      Author: tuerke
 ******************************************************************/
#include "geometrical.hpp"
#include "common.hpp"

namespace isis
{
namespace glance
{
namespace geometrical
{

orientation_type getOrientationMatrixFromPropMap ( const isis::util::PropertyMap &propmap )
{
	const orientation_type retMatrix (  propmap.getPropertyAs<isis::util::fvector3>( "rowVec" ),
										propmap.getPropertyAs<isis::util::fvector3>( "columnVec" ),
										propmap.getPropertyAs<isis::util::fvector3>( "sliceVec" ) );
	return retMatrix;
}

orientation_type getLatchedOrienation ( const orientation_type &orientation_matrix )
{
	orientation_type retMatrix;
	retMatrix.fill( 0 );
	const isis::util::fvector3 &rowVec = orientation_matrix.getRow( 0 );
	const isis::util::fvector3 &columnVec = orientation_matrix.getRow( 1 );
	const isis::util::fvector3 &sliceVec = orientation_matrix.getRow( 2 );

	size_t rB = rowVec.getBiggestVecElemAbs();
	size_t cB = columnVec.getBiggestVecElemAbs();
	size_t sB = sliceVec.getBiggestVecElemAbs();

	if( rB == cB ) {
		if( sB == 0 ) {
			rB = 1;
			cB = 2;
		} else if ( sB == 1 ) {
			rB = 2;
			cB = 0;
		} else if ( sB == 2 ) {
			rB = 0;
			cB = 1;
		}
	}

	if( rB == sB ) {
		if( cB == 0 ) {
			rB = 2;
			sB = 1;
		} else if ( cB == 1 ) {
			rB = 2;
			sB = 0;
		} else if ( cB == 2 ) {
			rB = 1;
			sB = 0;
		}
	}

	if( cB == sB ) {
		if( rB == 0 ) {
			cB = 1;
			sB = 2;
		} else if ( rB == 1 ) {
			cB = 2;
			sB = 0;
		} else if ( rB == 2 ) {
			cB = 1;
			sB = 0;
		}
	}

	retMatrix.elem( rB, 0 ) = rowVec[rB] < 0 ? -1 : 1;
	retMatrix.elem( cB, 1 ) =  columnVec[cB] < 0 ? -1 : 1;
	retMatrix.elem( sB, 2 ) = sliceVec[sB] < 0 ? -1 : 1;
	return retMatrix;
}


const orientation_type &getMatrixForPlaneOrientation ( const PlaneOrientation &planeOrientation )
{
	static const orientation_type axialMatrix ( isis::util::fvector3( -1, 0, 0 ),
			isis::util::fvector3( 0, 1, 0 ),
			isis::util::fvector3( 0, 0, 1 ) );

	static const orientation_type sagittalMatrix (  isis::util::fvector3( 0, 1, 0 ),
			isis::util::fvector3( 0, 0, -1 ),
			isis::util::fvector3( 1, 0, 0 ) );

	static const orientation_type coronalMatrix (   isis::util::fvector3( -1, 0, 0 ),
			isis::util::fvector3( 0, 0, -1 ),
			isis::util::fvector3( 0, 1, 0 ) );

	switch( planeOrientation ) {
	case AXIAL:
		return axialMatrix;
	case SAGITTAL:
		return sagittalMatrix;
	case CORONAL:
		return coronalMatrix;
	case NOT_SPECIFIED:
		LOG( isis::glance::util::Runtime, warning )
				<< "The matrix for the plane orientation \"NOT_SPECIFIED\" is not defined. Returning the \"AXIAL\" matrix!";
		return axialMatrix;
	}
}
isis::util::fvector4 mapCoordsToOrientation ( const isis::util::fvector4& coords, const isis::util::Matrix3x3< float >& orientationMatrix, PlaneOrientation orientation, bool back, bool absolute )
{
	isis::util::fvector3 ret = mapCoordsToOrientation( isis::util::fvector3( coords[0], coords[1], coords[2] ), orientationMatrix, orientation, back, absolute );
	return isis::util::fvector4( ret[0], ret[1], ret[2] );
}


isis::util::fvector3 mapCoordsToOrientation( const isis::util::fvector3 &coords, const isis::util::Matrix3x3<float> &orientationMatrix, PlaneOrientation orientation, bool back, bool absolute )
{
	isis::util::fvector3 retVec;
	if( back ) {
		retVec = getMatrixForPlaneOrientation(orientation).dot( orientationMatrix ).transpose().dot( coords );
	} else {
		retVec = getMatrixForPlaneOrientation(orientation).dot( orientationMatrix ).dot( coords );
	}
	if( absolute ) {
		return isis::util::fvector3( fabs( retVec[0] ), fabs( retVec[1] ), fabs( retVec[2] )  );
	} else {
		return retVec;
	}

}

} // end namespace geometrical
} // end namespace glance
} // end namespace isis
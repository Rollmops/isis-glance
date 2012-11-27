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
 * orientation.cpp
 *
 * Description:
 *
 *  Created on: Nov 20, 2012
 *      Author: tuerke
 ******************************************************************/
#include "orientation.hpp"
#include <CoreUtils/vector.hpp>

namespace isis {
namespace glance {
namespace util {

const Orientation::OrientationType Orientation::axialOrientation_ = isis::util::Matrix3x3<float> (isis::util::fvector3( -1, 0, 0 ),
			isis::util::fvector3( 0, 1, 0 ),
			isis::util::fvector3( 0, 0, 1 ));

const Orientation::OrientationType Orientation::sagittalOrientation_ = isis::util::Matrix3x3<float> (isis::util::fvector3( 0, 1, 0 ),
			isis::util::fvector3( 0, 0, -1 ),
			isis::util::fvector3( 1, 0, 0 ));

const Orientation::OrientationType Orientation::coronalOrientation_ = isis::util::Matrix3x3<float> (isis::util::fvector3( -1, 0, 0 ),
			isis::util::fvector3( 0, 0, -1 ),
			isis::util::fvector3( 0, 1, 0 ));

Orientation::Orientation( const OrientationType &orientation )
	: internalOrientation_(orientation)
{
}

Orientation::Orientation(const PlaneOrientation &planeOrientation)
{
	switch( planeOrientation) {
	case AXIAL:
		internalOrientation_ = axialOrientation_;
		break;
	case SAGITTAL:
		internalOrientation_ = sagittalOrientation_;
		break;
	case CORONAL:
		internalOrientation_ = coronalOrientation_;
		break;
	}

}

bool Orientation::isLatched() const
{
	const isis::util::fvector3 rowVec = internalOrientation_.getRow(0);
	const isis::util::fvector3 columnVec = internalOrientation_.getRow(1);
	const isis::util::fvector3 sliceVec = internalOrientation_.getRow(2);
	// we only have to check two vectors
	return rowVec.sum() == rowVec[rowVec.getBiggestVecElemAbs()]
	                              && sliceVec.sum() == sliceVec[sliceVec.getBiggestVecElemAbs()];
}

void Orientation::rotate(const float &x, const float &y, const float &z)
{
	const float x_ = (x / 180.0f) * M_PI;
	const float y_ = (y / 180.0f) * M_PI;
	const float z_ = (z / 180.0f) * M_PI;
	const float rotation [] = {	cos(y_) * cos(z_), -cos(x_) * sin(z_) + sin(x_) * sin(y_) * cos(z_), sin(x_) * sin(z_) + cos(x_) * sin(y_) * cos(z_),
								cos(y_) * sin(z_), cos(x_) * cos(z_) + sin(x_) * sin(y_) * sin(z_), -sin(x_) * cos(z_) + cos(x_) * sin(y_) * sin(z_),
								-sin(y_), sin(x_) * cos(y_), cos(x_) * cos(y_)};
	internalOrientation_ = internalOrientation_.dot(OrientationType(rotation));
}

}
}
}

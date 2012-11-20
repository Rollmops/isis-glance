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

}
}
}

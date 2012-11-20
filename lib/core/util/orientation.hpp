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
 * orientation.hpp
 *
 * Description:
 *
 *  Created on: Nov 20, 2012
 *      Author: tuerke
 ******************************************************************/
#ifndef _ISIS_GLANCE_ORIENTATION_HPP
#define _ISIS_GLANCE_ORIENTATION_HPP

#include <CoreUtils/matrix.hpp>

namespace isis {
namespace glance {
namespace util {

class Orientation
{
	typedef isis::util::Matrix3x3<float> OrientationType;
public:
	enum PlaneOrientation { AXIAL, SAGITTAL, CORONAL };

	Orientation( const OrientationType &orientation = axialOrientation_ );
	Orientation( const PlaneOrientation &planeOrientation );

	const OrientationType &get() const { return internalOrientation_; }

	bool is( const PlaneOrientation &planeOrientation ) const
	{
		const Orientation lhs( planeOrientation );
		return internalOrientation_ == lhs.get();
	}

private:

	OrientationType internalOrientation_; // stores the orientation matrix

	static const OrientationType axialOrientation_;
	static const OrientationType sagittalOrientation_;
	static const OrientationType coronalOrientation_;
};


}
}
}
#endif // _ISIS_GLANCE_ORIENTATION_HPP

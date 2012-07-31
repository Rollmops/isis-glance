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
 * bounding_box.hpp
 *
 * Description:
 *
 *  Created on: Jul 30, 2012
 *      Author: tuerke
 ******************************************************************/
#ifndef _ISIS_GLANCE_BOUNDING_BOX_HPP
#define _ISIS_GLANCE_BOUNDING_BOX_HPP

#include <CoreUtils/vector.hpp>
#include "image_container.hpp"
#include "util/geometrical.hpp"

namespace isis {
namespace glance {
namespace data {

class BoundingBox : public isis::util::FixedVector<std::pair<float, float>, 3 >
{
public:
	typedef isis::util::FixedVector<float,6> ExtentType;
	typedef isis::util::fvector4 MappedExtentType;
	
	void refresh( const ImageContainer &container );

	ExtentType asExtentType() const { return extent_; }
	MappedExtentType asMappedExtentType( isis::glance::geometrical::PlaneOrientation orientation ) const;

private:
	ExtentType extent_;

};

} // end namespace data
} // end namespace glance
} // end namespace isis

#endif // _ISIS_GLANCE_BOUNDING_BOX_HPP
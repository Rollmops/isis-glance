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
 * bounding_box.cpp
 *
 * Description:
 *
 *  Created on: Jul 30, 2012
 *      Author: tuerke
 ******************************************************************/
#include "bounding_box.hpp"

namespace isis {
namespace glance {
namespace data {

void BoundingBox::refresh ( const ImageContainer& container )
{
	for( unsigned short i = 0; i < 3; i++ ) {
		operator[](i).first = std::numeric_limits<float>::max();
		operator[](i).second = -std::numeric_limits<float>::max();
	}

	BOOST_FOREACH( ImageVector::const_reference image, container.getVector() ) {
		const ImageMetaProperties::size_type imageSize = image->image_size;
		const isis::util::fvector3 mappedVoxelSize = image->orientation_matrix_latched.dot( image->voxel_size );

		for( unsigned short i = 0; i < 2; i++ ) {
			for( unsigned short j = 0; j < 2; j++ ) {
				for( unsigned short k = 0; k < 2; k++ ) {
					const isis::util::ivector4 currentCorner ( i * imageSize[0], j * imageSize[1] , k * imageSize[2] );
					const isis::util::fvector3 currentPhysicalCorner = image->get().getPhysicalCoordsFromIndex( currentCorner );
					for ( unsigned short l = 0; l < 3; l++ ) {
						if( currentPhysicalCorner[l] < operator[](l).first ) {
							operator[](l).first = currentPhysicalCorner[l] - ( mappedVoxelSize[l] / 2. );
						}

						if( currentPhysicalCorner[l] > operator[](l).second ) {
							operator[](l).second = currentPhysicalCorner[l] + ( mappedVoxelSize[l] / 2. );
						}
					}
				}
			}
		}
	}
	extent_[0] = operator[](0).first;
	extent_[1] = operator[](0).second;
	extent_[2] = operator[](1).first;
	extent_[3] = operator[](1).second;
	extent_[4] = operator[](2).first;
	extent_[5] = operator[](2).second;
	
		
}

BoundingBox::MappedExtentType BoundingBox::asMappedExtentType(isis::glance::geometrical::PlaneOrientation orientation ) const
{
	MappedExtentType ret;
	switch( orientation ) {
	case geometrical::AXIAL:
		ret = MappedExtentType( operator[](0).first,
								operator[](1).first,
								fabs( operator[](0).second - operator[](0).first ),
								fabs( operator[](1).second - operator[](1).first ) );
		break;
	case geometrical::SAGITTAL:
		ret = MappedExtentType( operator[](1).first,
								operator[](2).first,
								fabs(  operator[](1).second - operator[](1).first ),
								fabs(  operator[](2).second - operator[](2).first ) );
		break;
	case geometrical::CORONAL:
		ret = MappedExtentType(   operator[](0).first,
								operator[](2).first,
								fabs(  operator[](0).second - operator[](0).first ),
								fabs(  operator[](2).second - operator[](2).first ) );
		break;
	case geometrical::NOT_SPECIFIED:
		break;
	}

	return ret;
}


} // end namespace data
} // end namespace glance
} // end namespace isis
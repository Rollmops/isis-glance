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
 * volume.cpp
 *
 * Description:
 *
 *  Created on: Jul 5, 2012
 *      Author: tuerke
 ******************************************************************/
#include "volume.hpp"
#include "data_handler.hpp"
#include "image.hpp"
#include <cstring>
#include <stdlib.h>

namespace isis
{
namespace glance
{
namespace data
{

void Volume::convertToType ( const types::ImageDataType &type )
{
	static_cast<isis::data::ValueArrayReference &>( *this ) = this->operator->()->convertByID( type );
}

Volume::Volume ( const isis::data::ValueArrayReference &src, const size_type &size, const Image *parentImage )
	: DataContainer< 3 > ( src, size ),
	  parentImage_( parentImage )
{}


DataHandler::permutation_type Volume::getPermutationSagittal( bool aligned32Bit ) const
{
	if( aligned32Bit ) {
		return parentImage_->permutationSagittalAligned32Bit_;
	} else {
		return parentImage_->permutationSagittal_;
	}
}



Slice Volume::extractSlice ( const geometrical::orientation_type &orientation, const ivec &coords,  bool force32BitAligned ) const
{
	const isis::data::ValueArrayBase *src = this->operator->();
	const size_t bytesPerElem = src->bytesPerElem();
	const size_t typeFac = bytesPerElem / sizeof( uint8_t );
	const size_type size = getSizeAsVector();
	size_type sliceSize;

	if( force32BitAligned ) {
		sliceSize = geometrical::get32BitAlignedSize<3>( size );
	} else {
		sliceSize = size;
	}

	const isis::util::fvector3 direction = orientation.getRow( isis::data::sliceDim ).norm();

	//we can define some special cases to increase performance
	if( abs( direction[2] ) == 1 ) {
		return extractSliceAxial( src, coords[isis::data::sliceDim], size, sliceSize, bytesPerElem, typeFac );
	} else if ( abs( direction[1] )  == 1 ) {
		return extractSliceCoronal( src, coords[isis::data::columnDim], size, sliceSize, bytesPerElem, typeFac );
	} else if ( abs( direction[0] ) == 1 ) {
		return Slice( DataHandler::extractSagittal( *this, coords[isis::data::rowDim], force32BitAligned ), Slice::size_type( sliceSize[1], sliceSize[2] ) );
	} else {
		// since extraction of sagittal slice is way more computationally expensive we use a optimized method for that (oil if available)
		return extractSliceGeneric( src, orientation, coords, force32BitAligned );
	}
}

Slice Volume::extractSliceAxial ( const isis::data::ValueArrayBase *src, const size_t &slice, const size_type &size, const size_type &sliceSize, const size_t &bytesPerElem, const size_t &typeFac ) const
{
	const uint8_t *srcPtr = static_cast<const uint8_t *>( src->getRawAddress().get() );
	const isis::data::ValueArrayReference dest = src->cloneToNew( sliceSize[0] * sliceSize[1] );
	uint8_t *destPtr = static_cast<uint8_t *>( dest->getRawAddress().get() );

	//we only can copy a whole slice if size == sliceSize for row and column dim
	if( size[0] == sliceSize[0] && size[1] == sliceSize[1] ) {
		memcpy( destPtr,
				srcPtr + size[0] * size[1] * slice * typeFac,
				size[0] * size[1] * bytesPerElem );
	} else {
		//we have to copy each row :-(
		for( size_t column = 0; column < size[1]; column++ ) {
			memcpy( destPtr + sliceSize[0] * column * typeFac,
					srcPtr + ( size[0] * size[1] * slice + size[0] * column ) * typeFac,
					sliceSize[0] * bytesPerElem );
		}
	}

	return Slice( dest, Slice::size_type( sliceSize[0], sliceSize[1] ) );
}

Slice Volume::extractSliceCoronal ( const isis::data::ValueArrayBase *src, const size_t &cslice, const size_type &size, const size_type &sliceSize, const size_t &bytesPerElem, const size_t &typeFac ) const
{
	const uint8_t *srcPtr = static_cast<const uint8_t *>( src->getRawAddress().get() );
	const isis::data::ValueArrayReference dest = src->cloneToNew( sliceSize[0] * sliceSize[2] );
	uint8_t *destPtr = static_cast<uint8_t *>( dest->getRawAddress().get() );

	for( size_t slice = 0; slice < size[2]; slice++ ) {
		memcpy( destPtr + sliceSize[0] * slice * typeFac,
				srcPtr + ( size[0] * cslice + size[0] * size[1] * slice ) * typeFac,
				sliceSize[0] * bytesPerElem );
	}

	return Slice( dest, Slice::size_type( sliceSize[0], sliceSize[2] ) );
}


Slice Volume::extractSliceGeneric ( const isis::data::ValueArrayBase *src, const geometrical::orientation_type &orientation, const ivec &coords, bool force32BitAligned ) const
{




}



} // end namespace data
} // end namespace glance
} // end namespace isis

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
 * image.hpp
 *
 * Description:
 *
 *  Created on: Jun 26, 2012
 *      Author: tuerke
 ******************************************************************/
#ifndef _ISIS_GLANCE_IMAGE_HPP
#define _ISIS_GLANCE_IMAGE_HPP

#include "image_base.hpp"
#include "util/signal.hpp"

namespace isis
{
namespace glance
{
namespace data
{

class Image : public ImageBase
{
public:
	typedef util::SharedPointer<Image> SharedPointer;

	/**
	 * Creates an isis::glance::data::Image from an existing isis::data::Image.
	 * If you wish the isis::glance::data::Image to have a certain data type you
	 * can use setProposedDataType and setUseProposedDataType to specify this type.
	 * \param image Ths isis::data::Image
	 */
	Image( const isis::data::Image &image );

	/**
	 * Creates an isis::glance::data::Image from an existing isis::data::Image with specified type.
	 * \param image The isis::data::Image
	 * \param type The type that specifies the type of each volume.
	 */
	Image( const isis::data::Image &image, const types::ImageDataType &type );

	/**
	 * Synchronizes the isis::glance::data::Image with the isis::data::Image
	 * specified by image.
	 * \param image The isis::data::Image that should be used for synchronizing.
	 * \param content Type of content that should be synchronized.
	 * \return True if synchronizing was successful. Otherwise returns false.
	 */
	bool synchronizeFrom( const isis::data::Image &image, const ImageContentType &content );

	/**
	 * Synchronizes the isis::glance::data::Image with the underlying isis::data::Image
	 * that can be accessed by the get() method.
	 * \param content Type of content that should be synchronized.
	 * \return True if synchronizing was successful. Otherwise false.
	 */
	bool synchronize( const ImageContentType &content ) { return synchronizeFrom( *isis_image_, content ); }

	/**
	 * Sets the data type that should be used for synchronizing of voxel content.
	 * \param type The data type used to synchronize.
	 * \note This method also calls the setForceTypedImage( true ).
	 */
	void setDataType( const types::ImageDataType &type ) { type_ = type; }

	types::ImageDataType getDataType() const { return type_; }

	static void setUseProposedDataType( const bool &use_proposed ) { forceProposedDataType_ = use_proposed; }
	static void setProposedDataType( const Image::ImageTypeGroup &type_group, const types::ImageDataType &data_type );

	//  //signals
	static util::Signal<void( const Image &, const types::ImageDataType & )> signal_conversion_begin;
	static util::Signal<void( const Image &, const types::ImageDataType & )> signal_conversion_end;
	static util::Signal<void( const Image &, const ImageContentType & )> signal_content_changed;

	void convertVolumesToType( const types::ImageDataType &type );
	
protected:
	bool synchronizeVoxelContentFrom( isis::data::Image image );
private:
	//we need to hold these properties for future calls of synchronize and synchronizeFrom
	types::ImageDataType type_;

	static bool forceProposedDataType_;
	static types::ImageDataType proposedScalar_;
	static types::ImageDataType proposedComplex_;
	static types::ImageDataType proposedColor_;
	static types::ImageDataType proposedVector_;

};

} // end namespace data
} // end namespace glance
} // end namespace isis


#endif // _ISIS_GLANCE_IMAGE_HPP
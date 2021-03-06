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
 * qt4_widget_base.cpp
 *
 * Description:
 *
 *  Created on: Jul 30, 2012
 *      Author: tuerke
 ******************************************************************/
#include "qt4_widget_base.hpp"

namespace isis
{
namespace glance
{
namespace qt4
{
namespace _internal
{

Qt4WidgetBase::Qt4WidgetBase ( QWidget *parent )
	: QWidget ( parent ),
	  layout_( new QVBoxLayout( parent ) )
{
	layout_->addWidget( this );
	layout_->setMargin( 0 );
}

} // end namespace _internal
} // end namespace qt4
} // end namespace glance
} // end namespace isis
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
 * widget_component.hpp
 *
 * Description:
 *
 *  Created on: Jul 14, 2012
 *      Author: tuerke
 ******************************************************************/
#ifndef _ISIS_GLANCE_WIDGET_COMPONENT_HPP
#define _ISIS_GLANCE_WIDGET_COMPONENT_HPP

#include <boost/shared_ptr.hpp>

#include <QWidget>
#include "util/widget_base.hpp"


namespace isis
{
namespace glance
{
namespace qt4
{

class WidgetComponent : public QWidget
{
	Q_OBJECT
public:
	typedef isis::glance::widget::WidgetBase<QWidget> WidgetBaseType;
	WidgetComponent( QWidget *parent, WidgetBaseType *widgetInterface );

	boost::shared_ptr< WidgetBaseType > get() const { return widgetInterface_; }
private:
	boost::shared_ptr< WidgetBaseType > widgetInterface_;

};

} // end namespace qt4
} // end namespace glance
} // end namespace isis

#endif // _ISIS_GLANCE_WIDGET_COMPONENT_HPP
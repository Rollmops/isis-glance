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
 * qt4_widget_base.hpp
 *
 * Description:
 *
 *  Created on: Jul 30, 2012
 *      Author: tuerke
 ******************************************************************/
#ifndef _ISIS_GLANCE_QT4_WIDGET_BASE_HPP
#define _ISIS_GLANCE_QT4_WIDGET_BASE_HPP

#include "util/widget_base.hpp"
#include <QWidget>
#include <QVBoxLayout>

namespace isis
{
namespace glance
{
namespace qt4
{
namespace _internal
{

class Qt4WidgetBase : public QWidget, public widget::WidgetBase
{
public:
	Qt4WidgetBase ( QWidget *parent = 0 );
private:
	QVBoxLayout *layout_;

};

} // end namespace _internal
} // end namespace qt4
} // end namespace glance
} // end namespace isis


#endif // _ISIS_GLANCE_QT4_WIDGET_BASE_HPP
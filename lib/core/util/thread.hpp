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
 * thread.hpp
 *
 * Description:
 *
 *  Created on: Jun 29, 2012
 *      Author: tuerke
 ******************************************************************/
#ifndef _ISIS_GLANCE_THREAD_HPP
#define _ISIS_GLANCE_THREAD_HPP

#include <boost/thread.hpp>
#include <boost/scoped_ptr.hpp>
#include <util/signal.hpp>

#include <iostream>

namespace isis
{
namespace glance
{
namespace util
{
class Thread : boost::noncopyable
{
protected:
	Thread();
public:
	virtual ~Thread();
	void start();
	void interrupt();
	void join();
	void yield();
	void sleep( const size_t &milliseconds );
	virtual void operator() ();

	virtual void run() = 0;

	boost::thread &get() { return *thread_; }
	const boost::thread &get() const { return *thread_; }

	bool isRunning() const { return running_; }

	Signal<void ()> signal_created;
	Signal<void ()> signal_started;
	Signal<void ()> signal_finished;
	Signal<void ()> signal_joined;
	Signal<void ()> signal_interrupted;
	Signal<void ()> signal_yielded;
	Signal<void( const size_t & ) > signal_sleep;

	void setDebugIdentification( const std::string &debugIdent ) { debugIdent_ = debugIdent; }

private:
	boost::shared_ptr< boost::thread > thread_;
	bool running_;
	std::string debugIdent_;
	boost::mutex mutex_;
};
} // end namespace util
} // end namespace glance
} // end namespace isis

#endif // _ISIS_GLANCE_THREAD_HPP
############################################################
# The ISIS-glance project
#
# CMake configuration file of the QT widget plugin
#
# Author: Erik Tuerke <etuerke@googlemail.com>
# Date: Wed, 27 Jun 2012 10:27:10 +0200
#
############################################################

include_directories(${CMAKE_SOURCE_DIR}/lib/qt4)
include_directories(${CMAKE_CURRENT_BINARY_DIR})
############################################################
# Qt stuff
############################################################
FIND_PACKAGE(Qt4 COMPONENTS QtCore QtGui REQUIRED)

set(QT_USE_QTUITOOLS TRUE)

INCLUDE(${QT_USE_FILE})

qt4_wrap_cpp(QT_WIDGET_MOC_FILES qt_widget.cpp
			OPTIONS -DBOOST_TT_HAS_OPERATOR_HPP_INCLUDED )


set(QT_WIDGET_TARGET_LIBRARIES ${QT_LIBRARIES} )
set(QT_WIDGET_SOURCE_FILES qt_widget.cpp )

add_library(isis_glanceWidget_Qt SHARED ${QT_WIDGET_SOURCE_FILES} ${QT_WIDGET_MOC_FILES} ${QT_LIBRARIES} )

message(STATUS "Linking following libraries to qt widget: ${QT_WIDGET_TARGET_LIBRARIES}")

target_link_libraries(isis_glanceWidget_Qt isis_glance isis_glance_qt4 ${ISIS_LIB_DEPENDS} ${QT_LIBRARIES})
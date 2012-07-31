FIND_PACKAGE(Qt4 REQUIRED)
INCLUDE(${QT_USE_FILE})
include_directories(${CMAKE_SOURCE_DIR}/lib/qt4)
include_directories(${CMAKE_SOURCE_DIR}/lib/widgets)

add_executable( widgetComponent widgetComponent.cpp )

target_link_libraries(widgetComponent ${Boost_LIBRARIES} ${ISIS_LIB} isis_glanceWidget_Qt )
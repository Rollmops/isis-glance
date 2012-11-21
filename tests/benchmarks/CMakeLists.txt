add_executable( orientationStressTest orientationStressTest.cpp )

target_link_libraries( orientationStressTest ${Boost_LIBRARIES} ${ISIS_LIB} isis_glance )
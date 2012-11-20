add_executable( threadTest threadTest.cpp )
add_executable( orientationTest orientationTest.cpp )


target_link_libraries(threadTest ${Boost_LIBRARIES} ${ISIS_LIB} isis_glance )
target_link_libraries(orientationTest ${Boost_LIBRARIES} ${ISIS_LIB} isis_glance )

############################################################
# add ctest targets
############################################################

add_test(NAME threadTest COMMAND threadTest)
add_test(NAME orientationTest COMMAND orientationTest)

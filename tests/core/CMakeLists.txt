add_executable( threadTest threadTest.cpp )

target_link_libraries(threadTest ${Boost_LIBRARIES} ${ISIS_LIB} isis_glance  )

############################################################
# add ctest targets
############################################################

add_test(NAME threadTest COMMAND threadTest)
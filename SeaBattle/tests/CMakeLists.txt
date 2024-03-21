find_package(GTest)

add_executable(Tests unittests.cpp pos_tests.cpp)
target_link_libraries(Tests PUBLIC ${GTEST_LIBRARIES} Ship)
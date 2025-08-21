cmake_minimum_required(VERSION 4.1)
project(TurtleTest)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(GTest REQUIRED)

add_executable(turtle_test
    testTurtle.cpp
    UserTurtleService.cpp
    MockTurtle.h
    turtleInterface.h
    UserTurtleService.h
)

target_link_libraries(turtle_test GTest::gtest GTest::gmock GTest::gtest_main)

target_include_directories(turtle_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}) 
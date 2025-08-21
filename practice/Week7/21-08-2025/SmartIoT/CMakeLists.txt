cmake_minimum_required(VERSION 4.1)
project(Thermostat)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(GTest REQUIRED)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_library(logic INTERFACE)
target_include_directories(logic INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(thermo_test
    test.cpp
)

target_link_libraries(thermo_test
    logic
    GTest::gtest
    GTest::gtest_main
    GTest::gmock
    GTest::gmock_main
)

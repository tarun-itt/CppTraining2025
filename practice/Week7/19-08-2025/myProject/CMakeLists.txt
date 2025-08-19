cmake_minimum_required(VERSION 4.1)
project(MyCppProject LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(mathUtils STATIC
    lib/src/mathUtils.cpp
)

target_include_directories(mathUtils PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/inc
)

add_executable(myProgram src/main.cpp)
target_link_libraries(myProgram mathUtils)

add_custom_command(TARGET myProgram POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    $<TARGET_FILE:myProgram>
    ${CMAKE_CURRENT_SOURCE_DIR}/myProgram
)

enable_testing()

find_library(GTEST_LIB gtest)
find_library(GTEST_MAIN_LIB gtest_main)

if(NOT GTEST_LIB OR NOT GTEST_MAIN_LIB)
    message(FATAL_ERROR "Google Test not found. Install libgtest-dev.")
endif()

add_executable(test_math test/test.cpp)
target_link_libraries(test_math mathUtils ${GTEST_LIB} ${GTEST_MAIN_LIB})
target_include_directories(test_math PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/lib/inc)

add_test(NAME test_math COMMAND test_math)
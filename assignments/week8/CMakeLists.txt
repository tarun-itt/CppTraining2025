cmake_minimum_required(VERSION 4.1)
project(MusicPlayer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Generate compile_commands.json for IntelliSense
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Set include directories
include_directories(inc)

# Set source files
set(SOURCES
    src/main.cpp
    src/BASSAudioManager.cpp
    src/SongLibrary.cpp
    src/PlaylistWriter.cpp
    src/Playlist.cpp
    src/PlaylistManager.cpp
    src/MusicPlayer.cpp
    src/Application.cpp
)

# Create main executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Set include directories for the target
target_include_directories(${PROJECT_NAME} PRIVATE inc)

# Use local BASS library
set(BASS_LIBRARY ${CMAKE_CURRENT_SOURCE_DIR}/lib/libbass.so)
set(BASS_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib)

if(NOT EXISTS ${BASS_LIBRARY})
    message(FATAL_ERROR "BASS library not found at ${BASS_LIBRARY}")
endif()

message("Using local BASS library: ${BASS_LIBRARY}")
target_include_directories(${PROJECT_NAME} PRIVATE ${BASS_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} ${BASS_LIBRARY})

# Find GTest for testing
find_package(GTest REQUIRED)

# Set test sources
set(TEST_SOURCES
    test/test_main.cpp
    test/test_SongLibrary.cpp
    test/test_StandardPlaylist.cpp
    test/test_MusicPlayer.cpp
    src/SongLibrary.cpp
    src/Playlist.cpp
    src/MusicPlayer.cpp
)

# Create test executable
add_executable(${PROJECT_NAME}_tests ${TEST_SOURCES})
target_include_directories(${PROJECT_NAME}_tests PRIVATE inc)
target_link_libraries(${PROJECT_NAME}_tests GTest::gtest GTest::gmock GTest::gtest_main)

# Enable testing
enable_testing()
add_test(NAME ${PROJECT_NAME}_tests COMMAND ${PROJECT_NAME}_tests) 
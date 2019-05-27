cmake_minimum_required(VERSION 2.6)
project(SimulationEngine)

# Configuration flags
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -std=c++0x")

# Source files
set(SOURCES
    main.cpp
    block.cpp
    walker.cpp
    history.cpp
    Wlk_Resources.cpp
)

# Header files
include_directories(${PROJECT_SOURCE_DIR})
#set(HEADERS
#    block.h
#    walker.h
#    history.h
#)
#
#include_directory(.)
#include_directory(${CMAKE_CURRENT_SOURCE_DIR})
#include_directories( ${CMAKE_BINARY_DIR} )

# libconfig++ via pkg-config
find_package(PkgConfig)
pkg_check_modules(LIBCONFIG libconfig++)
link_directories(${LIBCONFIG_LIBRARY_DIRS})
include_directories(${LIBCONFIG_INCLUDE_DIRS})

# Compile
add_executable( ${PROJECT_NAME} ${SOURCES} )

# Link
target_link_libraries( ${PROJECT_NAME} ${LIBCONFIG_LIBRARIES})

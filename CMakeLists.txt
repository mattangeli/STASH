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

# Compile
add_executable( ${PROJECT_NAME} ${SOURCES} )

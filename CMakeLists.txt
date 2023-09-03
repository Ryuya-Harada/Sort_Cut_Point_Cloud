cmake_minimum_required(VERSION 3.2 FATAL_ERROR)
project(test)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS OFF)

# Point Cloud Library (required)
#find_package(PCL 1.2 REQUIRED)
#include_directories(${PCL_INCLUDE_DIRS})
#link_directories(${PCL_LIBRARY_DIRS})
#add_definitions(${PCL_DEFINITIONS})

# Boost (required)
find_package(Boost REQUIRED COMPONENTS system)
include_directories(Boost::boost)

add_executable(cpp_cmake main.cpp)
target_link_libraries(cpp_cmake Boost::system)
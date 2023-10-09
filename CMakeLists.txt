cmake_minimum_required(VERSION 3.2 FATAL_ERROR)
project(test)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS OFF)

# Boost (required)
find_package(Boost REQUIRED COMPONENTS system)
include_directories(Boost::boost)

add_executable(cpp_cmake main.cpp)
target_link_libraries(cpp_cmake Boost::system)
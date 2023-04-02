cmake_minimum_required(VERSION 3.24)
project(Project_2)

set(CMAKE_CXX_STANDARD 17)

add_executable(Project_2 main.cpp test-unit/catch.hpp test-unit/test.cpp AdjacencyList.cpp AdjacencyList.h)

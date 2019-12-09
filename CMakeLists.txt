cmake_minimum_required(VERSION 3.10)
project(porr_swarms)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(gso-sequential)
add_executable(porr_swarms main.cpp fa-sequential/FireflyAlgorithm.cpp fa-sequential/FireflyAlgorithm.h)
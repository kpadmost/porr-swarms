cmake_minimum_required(VERSION 3.10)
project(porr_swarms)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(gso-sequential)
add_subdirectory(fa-sequential)
add_subdirectory(fa-omp)
add_subdirectory(gso-omp)
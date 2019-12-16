cmake_minimum_required(VERSION 3.10)
project(firefly_algorithm_omp)

set(CMAKE_CXX_STANDARD 14)



add_executable(firefly_algorithm_omp FireflyAlgorithm.cpp FireflyAlgorithm.h main.cpp)
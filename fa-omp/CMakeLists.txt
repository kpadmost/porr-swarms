cmake_minimum_required(VERSION 3.10)
project(firefly_algorithm_omp)

set(CMAKE_CXX_STANDARD 14)

find_package(OpenMP)

set(HEADERS
        FireflyAlgorithm.h
        )

set(SOURCES
        FireflyAlgorithm.cpp
        )

add_executable(firefly_algorithm_omp ${HEADERS} ${SOURCES} main.cpp)
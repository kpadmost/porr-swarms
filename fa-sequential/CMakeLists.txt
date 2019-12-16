cmake_minimum_required(VERSION 3.10)
project(firefly_algorithm_seq)

set(CMAKE_CXX_STANDARD 14)

set(HEADERS
        Parameters.hpp
        FireflyAlgorithm.h
    )

set(SOURCES
        FireflyAlgorithm.cpp
    )

add_executable(firefly_algorithm_seq ${HEADERS} ${SOURCES} main.cpp)
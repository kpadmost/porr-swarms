cmake_minimum_required(VERSION 3.10)
project(firefly_algorithm_cude LANGUAGES CXX CUDA)

set(HEADERS
        Parameters.hpp
        FireflyAlgorithm.h
    )

set(SOURCES
        FireflyAlgorithm.cpp
    )

add_executable(firefly_algorithm_cuda ${HEADERS} ${SOURCES} main.cu)
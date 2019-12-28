cmake_minimum_required(VERSION 3.10)
project(firefly_algorithm_omp)

set(CMAKE_CXX_STANDARD 14)

set(HEADERS
        Parameters.hpp
        FireflyAlgorithm.h
    )

set(SOURCES
        FireflyAlgorithm.cpp
    )

add_executable(firefly_algorithm_omp ${HEADERS} ${SOURCES} main.cpp)

find_package(OpenMP)
target_link_libraries(${PROJECT_NAME} PUBLIC OpenMP::OpenMP_CXX)
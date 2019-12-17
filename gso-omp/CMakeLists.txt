cmake_minimum_required(VERSION 3.10)
project(glowworm_swarms_omp)

set(CMAKE_CXX_STANDARD 14)


set(HEADERS
        Glowworm.h
        GlowwormSwarm.h
        Random.hpp)

set(SOURCES
        Glowworm.cc
        GlowwormSwarm.cc
        Parameters.hpp
        )


find_package(OpenMP)

add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES} main.cpp)
target_link_libraries(${PROJECT_NAME} PUBLIC OpenMP::OpenMP_CXX)
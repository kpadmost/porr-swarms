cmake_minimum_required(VERSION 3.10)
project(glowworm_swarms)

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

add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES} main.cpp)
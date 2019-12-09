cmake_minimum_required(VERSION 3.10)
project(glowworm_swarms)

set(CMAKE_CXX_STANDARD 14)


set(HEADERS
        Glowworm.h
        GlowwormSwarm.h
        Parameters.hpp
        )

set(SOURCES
        Glowworm.cc
        GlowwormSwarm.cc
        main.cpp)



add_executable(glowworm_swarms ${HEADERS} ${SOURCES} main.cpp)
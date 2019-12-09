cmake_minimum_required(VERSION 3.10)
project(glowworm_swarms)

set(CMAKE_CXX_STANDARD 17)


set(HEADERS
        Glowworm.h
        GlowwormSwarm.h
        Parameters.hpp
        GlowwormPopulation.h
)

set(SOURCES
        Glowworm.cc
        GlowwormSwarm.cc
        GlowwormPopulation.cc
)



add_executable(glowworm_swarms ${HEADERS} ${SOURCES} main.cpp)
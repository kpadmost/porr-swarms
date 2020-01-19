cmake_minimum_required(VERSION 3.10)
project(firefly_algorithm_cude)

set(CMAKE_CXX_STANDARD 14)
#set_source_files_properties(main.cpp PROPERTIES LANGUAGE CUDA)
set(CUDA_HOST_COMPILER "<path to compiler executable>")

set(HEADERS
        Parameters.hpp
        FireflyAlgorithm.h
    )

set(SOURCES
        FireflyAlgorithm.cpp
    )

add_executable(firefly_algorithm_cuda ${HEADERS} ${SOURCES} main.cpp)
cmake_minimum_required(VERSION 3.16)

project(ArchiversComparison)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -Werror")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Ofast -march=native")

add_executable(ArchiversComparison Main.cpp Benchmark.cpp Benchmark.hpp Wrappers.hpp)

target_link_libraries(ArchiversComparison
        ${CMAKE_SOURCE_DIR}/../lib/libzstd.a
        ${CMAKE_SOURCE_DIR}/../lib/liblz4.a)
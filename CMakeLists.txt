cmake_minimum_required(VERSION 3.16)

project(ArchiversComparison)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -Werror")

include_directories(include/)

add_subdirectory(test)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Ofast -march=native")

add_executable(ArchiversComparison src/Main.cpp src/Benchmark.cpp)

target_link_libraries(ArchiversComparison
        ${CMAKE_SOURCE_DIR}/../lib/libzstd.a
        ${CMAKE_SOURCE_DIR}/../lib/liblz4.a)
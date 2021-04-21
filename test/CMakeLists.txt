cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=leak -fsanitize=address -fsanitize=undefined")

find_package(GTest REQUIRED)
find_package(Threads REQUIRED)

add_executable(ArchiversComparisonTest testAll.cpp)

include_directories(${GTEST_INCLUDE_DIRS})

target_link_libraries(ArchiversComparisonTest
        ${GTEST_LIBRARIES}
        Threads::Threads
        ${CMAKE_SOURCE_DIR}/../lib/libzstd.a
        ${CMAKE_SOURCE_DIR}/../lib/liblz4.a)

add_Test(Test ArchiversComparisonTest)

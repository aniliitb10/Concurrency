cmake_minimum_required(VERSION 3.14)
project(Concurrency)

set(CMAKE_CXX_STANDARD 17)

set (GTEST_LIB_PATH "/home/anil/lib/googletest-release-1.8.0/googletest/libgtest.a")
set (GTEST_INCLUDE_PATH "/home/anil/lib/googletest-release-1.8.0/googletest/include/")
file(GLOB gTestSource "Test/*.cpp")

include_directories( ${GTEST_INCLUDE_PATH} )

add_executable(Concurrency main.cpp ${gTestSource})
target_link_libraries(Concurrency ${GTEST_LIB_PATH} pthread)
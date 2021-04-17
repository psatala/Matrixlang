cmake_minimum_required(VERSION 3.12) # version can be different

project(Matrixlang) #name of your project

add_subdirectory(googletest) # add googletest subdirectory

# this is so we can #include <gtest/gtest.h>
include_directories(googletest/include) 

# all source files
file(GLOB SOURCES
    src/*.cpp
)

# all test files
file(GLOB TESTS
    tests/*.cpp
)

add_executable(Matrixlang ${SOURCES}) # add main executable
add_executable(MatrixlangTests ${TESTS}) # add test executable

# link google test to this executable
target_link_libraries(MatrixlangTests PRIVATE gtest) 
cmake_minimum_required(VERSION 3.12)
project(math3dcpp)

set(CMAKE_CXX_STANDARD 20)

include_directories(Src)

add_library(math3dcpp
        Src/VectorImpl.cpp
        Src/Matrix.cpp
        Src/Quaternion.cpp
        Src/Vector.cpp
        Src/Coordinates.cpp Src/RigidBody.cpp Src/RigidBody.hpp)

# Uts
file(GLOB TEST_FILES Uts/*Test.cpp)

add_executable(Tests ${TEST_FILES})
target_link_libraries(Tests gtest gtest_main pthread math3dcpp)

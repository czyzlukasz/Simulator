cmake_minimum_required(VERSION 3.16)
project(Simulator)

set(CMAKE_CXX_STANDARD 20)

include_directories(Src)
include_directories(Src/Math/Src)

add_executable(Simulator
        Src/main.cpp
        Src/PlaneItem.cpp
        Src/PlaneStatus.cpp
        Src/Simulator.cpp
        Src/PlaneItems/PlaneEngine.cpp
        Src/PlaneItems/PlaneAirfoil.cpp
        Src/PlaneItems/PlaneAileron.cpp)

add_subdirectory(Src/Math)
target_link_libraries(Simulator math3dcpp)

# Uts
file(GLOB TEST_FILES Uts/*Test.cpp)

add_executable(SimulatorTests
    ${TEST_FILES}
    Src/PlaneItem.cpp
    Src/PlaneStatus.cpp
    Src/Simulator.cpp
    Src/PlaneItems/PlaneEngine.cpp
    Src/PlaneItems/PlaneEngine.cpp
    Src/PlaneItems/PlaneAirfoil.cpp)
target_link_libraries(SimulatorTests gtest gtest_main gmock pthread math3dcpp)

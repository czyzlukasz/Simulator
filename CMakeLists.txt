cmake_minimum_required(VERSION 3.14)

project(Gui LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Qt stuff
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
find_package(QT NAMES Qt6 Qt5 COMPONENTS Core Quick Widgets 3DCore 3DRender REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Quick Widgets 3DCore 3DRender REQUIRED)

# Simulator
# GoogleTest
add_subdirectory(gtest)
include_directories(${GTEST_INCLUDE_DIRS})

add_subdirectory(Simulator)

set(PROJECT_SOURCES
        main.cpp
        SimulatorInterface.cpp
        qml.qrc
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Gui
        ${PROJECT_SOURCES}
    )
else()
    add_executable(Gui
        ${PROJECT_SOURCES}
    )
endif()

target_compile_definitions(Gui
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(Gui
  PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::3DRender)

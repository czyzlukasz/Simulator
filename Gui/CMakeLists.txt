cmake_minimum_required(VERSION 3.14)

project(Gui LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core Quick Widgets 3DCore 3DRender REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Quick Widgets 3DCore 3DRender REQUIRED)

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
    if(ANDROID)
        add_library(Gui SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(Gui
          ${PROJECT_SOURCES}
        )
    endif()
endif()

target_compile_definitions(Gui
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(Gui
  PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::3DRender)

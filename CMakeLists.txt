cmake_minimum_required(VERSION 3.5)

project(TestCase LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Charts REQUIRED)

if(ANDROID)
  add_library(TestCase SHARED
    src/main.cpp
    src/thread_xy.cpp
    src/mainwindow.cpp
    src/mainwindow.h
    src/thread_xy.h
    src/mainwindow.ui
    src/icons.qrc
  )
else()
  add_executable(TestCase
    src/main.cpp
    src/thread_xy.cpp
    src/mainwindow.cpp
    src/mainwindow.h
    src/thread_xy.h
    src/mainwindow.ui
    src/icons.qrc
  )
endif()

target_link_libraries(TestCase PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Charts)

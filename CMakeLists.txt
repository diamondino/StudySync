cmake_minimum_required(VERSION 3.21)
project(StudyPlanner LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

qt_add_executable(StudyPlanner
        src/main.cpp
)

target_include_directories(StudyPlanner PRIVATE include src)
target_link_libraries(StudyPlanner PRIVATE Qt6::Widgets)
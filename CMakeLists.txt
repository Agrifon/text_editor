cmake_minimum_required(VERSION 4.4)

project(TextEditor VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
add_subdirectory(core)
add_subdirectory(gui)

option(BUILD_TESTS "Build tests" ON)
if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

add_executable(${PROJECT_NAME} app/src/main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE gui)

message(STATUS "Project configured successfully!")


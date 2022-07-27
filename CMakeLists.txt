cmake_minimum_required(VERSION 3.22)
project(openCV)

set(CMAKE_CXX_STANDARD 14)

#find_library(OpenCV)
find_package(OpenCV)

include_directories(${OpenCV_INCLUDE_DIRS})
set(CMAKE_CXX_STANDARD 11)

add_executable(openCV src/main.cpp src/mission1.cpp src/mission1.h)

target_link_libraries(openCV ${OpenCV_LIBS})

cmake_minimum_required(VERSION 3.8)
project(Traffic-Network-Model)

set(CMAKE_CXX_STANDARD 11)
aux_source_directory(./src DIR_SRCS)
add_executable(Traffic-Network-Model ${DIR_SRCS} src/TrafficLight.cpp src/TrafficLight.h src/CrossRoad.cpp src/CrossRoad.h)

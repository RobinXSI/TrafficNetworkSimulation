cmake_minimum_required(VERSION 2.8.4)
project(TrafficNetworkSimulation)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Node.h Node.cpp SimulationWorld.h SimulationWorld.cpp)
add_executable(TrafficNetworkSimulation ${SOURCE_FILES})
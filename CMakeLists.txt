cmake_minimum_required(VERSION 2.8.4)
project(TrafficNetworkSimulation)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp SimulationWorld.h SimulationWorld.cpp Node.h Node.cpp Link.h Link.cpp )
add_executable(TrafficNetworkSimulation ${SOURCE_FILES})
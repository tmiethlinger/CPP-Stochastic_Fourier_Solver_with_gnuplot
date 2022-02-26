cmake_minimum_required(VERSION 3.7)

add_definitions(-std=c++17)

set(CXX_FLAGS "-Wall -O2 -pthread")
set(CMAKE_CXX_FLAGS "${CXX_FLAGS}")

project(StochasticFourierSolver)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
add_executable(StochasticFourierSolver src/main.cpp src/D2Fourier.cpp src/D2Gauss.cpp src/Fourier.cpp src/Gauss.cpp src/GnuplotFunctionViewer.cpp src/StochasticSolver.cpp)

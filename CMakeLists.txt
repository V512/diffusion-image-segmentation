cmake_minimum_required(VERSION 3.10)

project(Diffusion)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(OpenCV REQUIRED )

add_executable(Diffusion main.cpp diffusion.cpp diffusion.h neighborStruct.cpp neighborStruct.h phi.h phi.cpp timeMeasurement.h)

include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/)

link_directories( ${CMAKE_BINARY_DIR}/bin)

target_link_libraries( Diffusion ${OpenCV_LIBS} )
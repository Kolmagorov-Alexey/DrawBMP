cmake_minimum_required(VERSION 3.11)

project(DrawBMP CXX)
set(CMAKE_CXX_STANDARD 17)

add_executable(DrawBMP src/main.cpp src/bmp.h src/bmp.cpp) 
cmake_minimum_required(VERSION 3.19)
project(TSN_2022_winter)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,--stack,999999")


add_executable(TSN_2022_winter main.cpp)
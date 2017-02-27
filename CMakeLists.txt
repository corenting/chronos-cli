cmake_minimum_required(VERSION 3.6)
project(chronos_cli)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp)
add_executable(chronos_cli ${SOURCE_FILES})
cmake_minimum_required(VERSION 3.6)
project(chronos_cli)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES src/main.cpp)
FIND_PACKAGE(Boost 1.40 COMPONENTS program_options REQUIRED)
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})
add_executable(chronos_cli ${SOURCE_FILES})
TARGET_LINK_LIBRARIES(chronos_cli ${Boost_LIBRARIES})
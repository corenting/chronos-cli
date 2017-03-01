cmake_minimum_required(VERSION 3.6)
project(chronos_cli)

set(CMAKE_CXX_STANDARD 14)
set(SOURCE_FILES src/main.cpp src/http_requests.cpp src/http_requests.h)
add_executable(chronos_cli ${SOURCE_FILES})

# Boost
find_package(Boost 1.40 COMPONENTS REQUIRED program_options)
target_link_libraries(chronos_cli ${Boost_LIBRARIES})
include_directories(${Boost_INCLUDE_DIR})
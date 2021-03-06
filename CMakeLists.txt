cmake_minimum_required(VERSION 3.7)
project(chronos_cli)

set(CMAKE_CXX_STANDARD 14)
set(SOURCE_FILES src/main.cpp src/http_requests.cpp src/http_requests.h src/actions.cpp src/actions.h src/schedule.cpp src/schedule.h src/models/group.cpp src/models/group.h src/date.cpp src/date.h src/display/display.h src/models/event.cpp src/models/event.h src/display/line_display.cpp src/display/line_display.h src/json_parser.cpp src/json_parser.h src/group_cache.cpp src/group_cache.h src/api_token.h src/display/display.cpp)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
find_package(cpprestsdk REQUIRED)

set (Boost_USE_MULTITHREAD ON)
find_package(Boost 1.40 COMPONENTS REQUIRED system program_options date_time filesystem)
include_directories(${Boost_INCLUDE_DIR})

add_executable(chronos_cli ${SOURCE_FILES})
link_libraries("-static")
target_link_libraries(chronos_cli Threads::Threads cpprestsdk::cpprest ${Boost_LIBRARIES})
install(TARGETS chronos_cli DESTINATION bin)

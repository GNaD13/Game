cmake_minimum_required(VERSION 3.7)

project(Pong)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

file(GLOB SOURCES src/*.cpp)
add_executable(Pong ${SOURCES})
target_link_libraries(Pong ${SDL2_LIBRARIES})

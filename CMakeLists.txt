cmake_minimum_required(VERSION 3.26)
project(PulverPlay)

set(CMAKE_CXX_STANDARD 23)

add_definitions(-DSDL_MAIN_HANDLED)
add_executable(PulverPlay main.cpp
        Atom.cpp
        Atom.h)

target_link_libraries(PulverPlay SDL2)
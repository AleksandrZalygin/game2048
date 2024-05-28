cmake_minimum_required(VERSION 3.25)
project(game2048)

set(CMAKE_CXX_STANDARD 14)

add_executable(game2048
        main.cpp game.h game.cpp)

cmake_minimum_required(VERSION 3.17)
project(game_of_life)

set(CMAKE_CXX_STANDARD 20)

add_executable(game_of_life main.cpp world.cpp cell.cpp rules.cpp)
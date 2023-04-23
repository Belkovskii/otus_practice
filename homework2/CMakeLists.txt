cmake_minimum_required(VERSION 3.5)

project(02.game)

add_executable(game 
    stringUtils.cpp
    stringUtils.h 
    mapUtils.cpp
    mapUtils.h
    game.cpp
)

set_target_properties(game PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)
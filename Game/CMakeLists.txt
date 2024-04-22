cmake_minimum_required(VERSION 3.29)

project(Game)

set(CMAKE_CXX_STANDARD 20)

# Include both source and header files
add_executable(Game src/game.cpp src/game.h)

# Link with JellyEngine library and include its headers
target_link_libraries(Game PUBLIC JellyEngine)
target_include_directories(Game PUBLIC ../Engine/src)
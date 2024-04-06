cmake_minimum_required(VERSION 3.29)

project(Game)

set(CMAKE_CXX_STANDARD 20)

add_executable(Game src/game.cpp src/game.h)  # Include both source and header files

target_link_libraries(Game PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../Engine/out/JellyEngine.dll)  # Link with JellyEngine library
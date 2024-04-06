cmake_minimum_required(VERSION 3.29)

project(Game)

set(CMAKE_CXX_STANDARD 20)

add_executable(Game src/game.cpp src/game.h)  # Include both source and header files

#target_include_directories(), glm etc.

#target_link_libraries(Game PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../Engine/out/Debug/JellyEngine.lib)  # Link with JellyEngine library
target_link_libraries(Game PUBLIC JellyEngine)  # Link with JellyEngine library

target_include_directories(Game PUBLIC ../Engine/src)
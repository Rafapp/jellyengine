cmake_minimum_required(VERSION 3.29)

project(Game)

set(CMAKE_CXX_STANDARD 20)

add_executable(Game src/game.cpp src/game.h)

target_include_directories(Game PRIVATE ../Engine/src)
target_link_directories(Game PRIVATE ../Engine)
target_link_libraries(Game PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../Engine/JellyEngine.dll)

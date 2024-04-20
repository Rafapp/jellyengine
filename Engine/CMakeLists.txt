cmake_minimum_required(VERSION 3.29)

project(JellyEngine)

set(CMAKE_CXX_STANDARD 20)

set(HEADER_FILES
	src/JellyEngine.h
)

set(SOURCE_FILES
	src/JellyEngine.cpp
)

add_library(JellyEngine STATIC ${SOURCE_FILES} ${HEADER_FILES})

# Library headers
target_include_directories(JellyEngine PUBLIC "libraries/glad/include")
target_include_directories(JellyEngine PUBLIC "libraries/glfw/include")

# Cmake library header subdirectories
add_subdirectory("libraries/glad") # opengl loader
add_subdirectory("libraries/glfw") # window and input mgmt

target_link_libraries(JellyEngine PUBLIC glad glfw)


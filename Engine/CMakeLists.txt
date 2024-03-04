cmake_minimum_required(VERSION 3.29)

project(JellyEngine)

set(CMAKE_CXX_STANDARD 20)

set(HEADER_FILES
	src/JellyEngine.h
)

set(SOURCE_FILES
	src/JellyEngine.cpp
)

add_library(JellyEngine SHARED ${SOURCE_FILES} ${HEADER_FILES})
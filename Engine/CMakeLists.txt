cmake_minimum_required(VERSION 3.29)

project(JellyEngine)

set(CMAKE_CXX_STANDARD 20)

set(HEADER_FILES
	src/jellyEngine.h
	src/input.h
	src/renderer.h
	src/camera.h
	src/shader.h
	src/gameObject.h
	src/mesh.h
	src/model.h
)

set(SOURCE_FILES
	src/jellyEngine.cpp
	src/input.cpp
	src/renderer.cpp
	src/camera.cpp
	src/shader.cpp
	src/gameObject.cpp
	src/mesh.cpp
	src/model.cpp
)

add_library(JellyEngine STATIC ${SOURCE_FILES} ${HEADER_FILES})

# Library headers
target_include_directories(JellyEngine PUBLIC "libraries/glad/include")
target_include_directories(JellyEngine PUBLIC "libraries/glfw/include")
target_include_directories(JellyEngine PUBLIC "libraries/glm")
target_include_directories(JellyEngine PUBLIC "libraries/assimp/include")

# Cmake library header subdirectories
add_subdirectory("libraries/glad") # opengl loader
add_subdirectory("libraries/glfw") # window dispatcher and input mgmt
add_subdirectory("libraries/glm") # math
add_subdirectory("libraries/assimp") # 3D model loading

# Set resources folder
target_compile_definitions(JellyEngine PUBLIC RESOURCES_PATH="${CMAKE_CURRENT_SOURCE_DIR}/../Game/resources/")

target_link_libraries(JellyEngine PUBLIC glad glfw glm assimp)


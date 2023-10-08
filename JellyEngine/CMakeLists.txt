# CMakeList.txt : CMake project for JellyEngine, include source and define
# project specific logic here.
#
#Definitions
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("JellyEngine")

#Remove GLFW examples from build
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

# Add library subdirectories
#add_subdirectory("libraries/assimp")
add_subdirectory("libraries/glfw")

# Add source to this project's executable.
add_executable (JellyEngine "JellyEngine.cpp" "JellyEngine.h")

# USE THIS IF DEVELOPING
#target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC RESOURCES_PATH="${CMAKE_CURRENT_SOURCE_DIR}/resources/")

# USE THIS ON PRODUCTION
target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC RESOURCES_PATH="./resources/") 

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET JellyEngine PROPERTY CXX_STANDARD 20)
endif()

#Link libraries
find_package(OpenGL REQUIRED)
target_compile_definitions(${CMAKE_PROJECT_NAME} PUBLIC GLFW_DLL)

#target_link_libraries("${CMAKE_PROJECT_NAME}" PRIVATE assimp glfw OpenGL::GL)
target_link_libraries("${CMAKE_PROJECT_NAME}" PRIVATE glfw OpenGL::GL)


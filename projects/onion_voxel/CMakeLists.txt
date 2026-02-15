cmake_minimum_required(VERSION 3.20)

project(onion_voxel LANGUAGES CXX)

# Modules
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# Dependencies (GLFW, GLAD, GLM, stb, Assimp optional)
include(FetchContent)

include(FetchGLFW)
include(FetchGLM)
include(FetchSTB)

add_subdirectory(external/glad)

#add_subdirectory(src/shared)
add_subdirectory(src/client)
add_subdirectory(src/server)

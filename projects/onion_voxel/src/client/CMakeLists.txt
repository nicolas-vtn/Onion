cmake_minimum_required(VERSION 3.20)

project(onion_voxel_client LANGUAGES CXX)

add_executable(onion_voxel
    "main.cpp"
    "src/Client.cpp"

	"src/renderer/Renderer.cpp"
)

target_link_libraries(onion_voxel
    PUBLIC
        glfw
        glad
        glm
        stb
    PRIVATE
        onion_voxel_server
)

target_compile_features(onion_voxel PRIVATE cxx_std_20)

target_include_directories(onion_voxel
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

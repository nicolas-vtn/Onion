cmake_minimum_required(VERSION 3.21)

project(Onion
    VERSION 0.1.0
    DESCRIPTION "Onion Playground"
    LANGUAGES CXX
)

# ---- Global C++ standard ----
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ---- Warnings ----
if(MSVC)
    add_compile_options(/W4 /permissive-)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# ---- Output directories ----
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# ---- Subdirectories ----
add_subdirectory(projects/helloword)
add_subdirectory(libs/datetime)
add_subdirectory(libs/event)
add_subdirectory(libs/timer)

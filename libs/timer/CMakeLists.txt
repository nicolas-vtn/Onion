cmake_minimum_required(VERSION 3.20)

project(onion_timer LANGUAGES CXX)

# ---- Library ----
add_library(onion_timer
    Timer.cpp
)

target_include_directories(onion_timer
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_compile_features(onion_timer PUBLIC cxx_std_20)

set_target_properties(onion_timer PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)

# ---- Tests ----
option(ONION_TIMER_BUILD_TESTS "Build Timer tests" ON)

if (ONION_TIMER_BUILD_TESTS)
    add_subdirectory(tests)
endif()

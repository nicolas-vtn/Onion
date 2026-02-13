cmake_minimum_required(VERSION 3.20)

project(onion_datetime LANGUAGES CXX)

# ---- Library ----
add_library(onion_datetime
    DateTime.cpp
)

target_include_directories(onion_datetime
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_compile_features(onion_datetime PUBLIC cxx_std_20)

set_target_properties(onion_datetime PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)

# ---- Tests ----
option(ONION_DATETIME_BUILD_TESTS "Build DateTime tests" ON)

if (ONION_DATETIME_BUILD_TESTS)
    add_subdirectory(tests)
endif()

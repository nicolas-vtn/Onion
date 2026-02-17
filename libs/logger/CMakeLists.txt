cmake_minimum_required(VERSION 3.20)

project(onion_logger LANGUAGES CXX)


# ---- Dependency : onion_datetime ----
if (NOT TARGET onion_datetime)
    message(FATAL_ERROR "onion_datetime is required for onion_logger")
endif()

# ---- Library ----
add_library(onion_logger
    Logger.cpp
)

target_include_directories(onion_logger
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_compile_features(onion_logger PUBLIC cxx_std_20)

set_target_properties(onion_logger PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)

# ---- Link dependency ----
target_link_libraries(onion_logger
    PUBLIC
        onion_datetime
)

# ---- Tests ----
option(ONION_LOGGER_BUILD_TESTS "Build Logger tests" ON)

if (ONION_LOGGER_BUILD_TESTS)
    add_subdirectory(tests)
endif()

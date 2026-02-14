cmake_minimum_required(VERSION 3.20)

project(onion_event LANGUAGES CXX)

# ---- Library ----
add_library(onion_event INTERFACE)
target_include_directories(onion_event INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
 
set_target_properties(onion_event PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)

# ---- Tests ----
option(ONION_EVENT_BUILD_TESTS "Build Event tests" ON)

if (ONION_EVENT_BUILD_TESTS)
    add_subdirectory(tests)
endif()

add_executable(helloword
    main.cpp
)

target_compile_features(helloword PRIVATE cxx_std_20)

target_include_directories(helloword
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)
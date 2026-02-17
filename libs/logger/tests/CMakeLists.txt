add_executable(onion_logger_tests
    main.cpp
)

target_link_libraries(onion_logger_tests
    PRIVATE
        onion_logger
)

target_compile_features(onion_logger_tests PRIVATE cxx_std_20)

set_target_properties(onion_logger_tests PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)

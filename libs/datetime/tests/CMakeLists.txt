add_executable(onion_datetime_tests
    main.cpp
)

target_link_libraries(onion_datetime_tests
    PRIVATE
        onion_datetime
)

target_compile_features(onion_datetime_tests PRIVATE cxx_std_20)

set_target_properties(onion_datetime_tests PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)

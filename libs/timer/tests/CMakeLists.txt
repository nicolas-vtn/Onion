add_executable(onion_timer_tests
    main.cpp
)

target_link_libraries(onion_timer_tests
    PRIVATE
        onion_timer
)

target_compile_features(onion_timer_tests PRIVATE cxx_std_20)

set_target_properties(onion_timer_tests PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)

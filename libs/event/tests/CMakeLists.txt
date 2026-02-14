add_executable(onion_event_tests
    main.cpp
)

target_link_libraries(onion_event_tests
    PRIVATE
        onion_event
)

target_compile_features(onion_event_tests PRIVATE cxx_std_20)

set_target_properties(onion_event_tests PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)

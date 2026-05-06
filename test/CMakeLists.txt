add_executable(run_tests test_polynom.cpp)

target_link_libraries(run_tests 
    PRIVATE 
    poly_lib 
    gtest_main
)
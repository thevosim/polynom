
add_library(poly_lib polynom.cpp)

target_include_directories(poly_lib PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../include")
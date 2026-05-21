cmake_minimum_required(VERSION 3.10)
cmake_policy(SET CMP0135 NEW)
project(polynom)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/heads/main.zip
)
FetchContent_MakeAvailable(googletest)

add_subdirectory(src)
add_subdirectory(test)
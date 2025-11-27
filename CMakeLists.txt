cmake_minimum_required(VERSION 3.26)
project(feedback_controller LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_compile_options(-Wconversion -Werror -Wall -Wextra -Wpedantic)

# Header-only interface library
add_library(feedback_controller_interface INTERFACE)
target_include_directories(feedback_controller_interface INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# bang-bang controller example
add_subdirectory(example)
add_executable(simple_perf main.cpp)

target_link_libraries(simple_perf
    PRIVATE sim_hal
)

target_include_directories(simple_perf PRIVATE
    ${CMAKE_SOURCE_DIR}/components/hal/include
)
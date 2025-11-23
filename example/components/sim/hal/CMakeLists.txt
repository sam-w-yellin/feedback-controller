add_library(sim_hal STATIC
    src/adc.cpp
    src/gpio.cpp
)

target_include_directories(sim_hal PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../../hal/include
)
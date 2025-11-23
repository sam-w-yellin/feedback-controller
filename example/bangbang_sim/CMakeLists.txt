add_executable(bangbang_sim main.cpp)

# Link interface + sim hal
target_link_libraries(bangbang_sim
    PRIVATE feedback_controller_interface
    PRIVATE sim_hal
)

# Add include directories for plugins + hal
# (Paths are relative to this CMakeLists.txt)
target_include_directories(bangbang_sim PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../components/feedback_controller/plugins/actuators/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../components/feedback_controller/plugins/feedback/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../components/feedback_controller/plugins/laws/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../components/hal/include
)
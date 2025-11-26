add_executable(bangbang_setpoint_sim main.cpp)

target_link_libraries(bangbang_setpoint_sim
    PRIVATE feedback_controller_interface
    PRIVATE sim_hal
)

target_include_directories(bangbang_setpoint_sim PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../components/feedback_controller/plugins/actuators/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../components/feedback_controller/plugins/feedback/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../components/feedback_controller/plugins/laws/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../components/hal/include
)
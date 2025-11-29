add_executable(template_perf main.cpp)

target_link_libraries(template_perf
    PRIVATE feedback_controller_interface
    PRIVATE sim_hal
)

target_include_directories(template_perf PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../../components/feedback_controller/plugins/actuators/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../../components/feedback_controller/plugins/feedback/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../../components/feedback_controller/plugins/laws/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../../components/hal/include
)
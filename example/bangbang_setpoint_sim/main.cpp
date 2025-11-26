#include <fstream>
#include <print>

#include "adc.hpp"
#include "adc_feedback.hpp"
#include "bangbang_setpoint.hpp"
#include "feedback_controller_interface.hpp"
#include "gpio.hpp"
#include "gpio_actuator.hpp"

struct SimplePlant
{
    int temperature_c = 25;

    void step(bool cooling_on)
    {
        if (cooling_on)
        {
            temperature_c -= 1;
        }
        else
        {
            temperature_c += 1;
        }
    }

    // convert °C → ADC raw units (0–65535)
    // assume 0.1 deg c per raw tick
    uint16_t adc_reading() const
    {
        return static_cast<uint16_t>(temperature_c * 10);
    }
};

std::string FormatState(const auto& state)
{
    return std::format("TEMP_C: {}, GPIO: {}, CMD: {}\n", state.feedback_state.first,
                       state.actuator_state, state.control_state.last_command);
};

void RunTecSim(auto& controller, auto& sim_adc, auto& sim_gpio)
{
    std::ofstream log("sim.log");
    if (!log)
    {
        std::println("Failed to open sim.log.");
        return;
    }

    SimplePlant plant;
    for (int i = 0; i < 1000; i++)
    {
        sim_adc.SetRawValue(plant.adc_reading());
        auto maybe_state = controller.Step();
        if (!maybe_state.has_value())
        {
            std::println("Error: {}", maybe_state.error());
            break;
        }
        bool cooling_on = sim_gpio.Read().value();
        plant.step(cooling_on);
        log << FormatState(maybe_state.value());
    }
}

int main()
{
    // Simulated hardware
    SimulatedAdc adc;
    SimulatedGpio gpio;

    // Bang-bang control law
    BangBangSetpointLaw law(60 /* setpoint deg c */);

    // ADC Feedback
    auto convert_adc = [](uint16_t raw) -> BangBangSetpointLaw::Measurement
    { return static_cast<BangBangSetpointLaw::Measurement>(raw) / 10; };
    AdcFeedback<BangBangSetpointLaw, decltype(convert_adc)> feedback(adc, convert_adc);

    // GPIO Actuator
    auto convert_gpio = [](bool cmd) -> BangBangSetpointLaw::Command { return cmd; };
    GpioActuator<BangBangSetpointLaw, decltype(convert_gpio)> actuator(gpio, convert_gpio);

    // Integrated controller
    Controller<BangBangSetpointLaw, decltype(feedback), decltype(actuator)> controller(feedback, actuator,
                                                                               law);

    auto init = controller.Initialize();

    if (!init.has_value())
    {
        std::println("Controller init error: {}", init.error());
        return 1;
    }

    RunTecSim(controller, adc, gpio);
    return 0;
}
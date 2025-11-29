#include <fstream>
#include <print>

#include "adc.hpp"
#include "adc_feedback.hpp"
#include "bangbang_range.hpp"
#include "feedback_controller_interface.hpp"
#include "gpio.hpp"
#include "gpio_actuator.hpp"


int main()
{
    // Simulated hardware
    SimulatedAdc adc;
    SimulatedGpio gpio;

    // Bang-bang control law
    BangBangRangeLaw law(20 /* min */, 80 /* max */);

    // ADC Feedback
    AdcFeedback<BangBangRangeLaw, [](uint16_t raw) -> BangBangRangeLaw::Measurement
                { return static_cast<BangBangRangeLaw::Measurement>(raw) / 10; }>
        feedback(adc);

    // GPIO Actuator
    GpioActuator<BangBangRangeLaw, [](bool cmd) -> BangBangRangeLaw::Command { return cmd; }>
        actuator(gpio);

    // Integrated controller
    Controller<BangBangRangeLaw, decltype(feedback), decltype(actuator)> controller(feedback,
                                                                                    actuator, law);

    static_cast<void>(controller.Initialize());

    for (int i = 0; i < 100000000; i++) {
        static_cast<void>(controller.Step());
    }

    return 0;
}
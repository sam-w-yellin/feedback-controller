#pragma once

#include "gpio_interface.hpp"
#include "feedback_controller_interface.hpp"

template <ControlLaw LAW, typename Converter>
class GpioActuator {
public:
    using Command = typename LAW::Command;
    using State   = bool; // actual GPIO output state

    GpioActuator(Gpio& gpio, Converter converter)
        : gpio_(gpio), convert_(converter) {}

    std::expected<State, std::string> Write(const Command& cmd) {
        State gpio_state = convert_(cmd); // convert command -> bool
        const auto err = gpio_.Set(gpio_state);
        if (err.has_value()) {
            return std::unexpected(std::format("Failed to set GPIO: {}", err.value()));
        }
        return gpio_state;
    }

    std::optional<std::string> Configure() {
        const auto configure_result = gpio_.Configure(Gpio::Output);
        if (configure_result.has_value()) {
            return std::make_optional(std::format("GPIO configure failed: {}", configure_result.value()));
        }
        return {};
    }

private:
    Gpio& gpio_;
    Converter convert_;
};
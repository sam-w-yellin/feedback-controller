#pragma once

#include "feedback_controller_interface.hpp"
#include "gpio_interface.hpp"

template <ControlLaw LAW, typename Converter>
class GpioActuator
{
   public:
    using Command = typename LAW::Command;
    using State = bool; 

    GpioActuator(Gpio& gpio, Converter converter) : gpio_(gpio), Convert(converter) {}

    std::expected<State, std::string> Write(const Command& cmd)
    {
        State gpio_state = Convert(cmd);
        const auto result = gpio_.Set(gpio_state);
        if (!result)
        {
            return std::unexpected(std::format("Failed to set GPIO: {}", result.error()));
        }
        return gpio_state;
    }

    std::expected<void, std::string> Configure()
    {
        const auto configure_result = gpio_.Configure(Gpio::Output);
        if (!configure_result)
        {
            return std::unexpected(
                std::format("GPIO configure failed: {}", configure_result.error()));
        }
        return {};
    }

    Converter Convert;
   private:
    Gpio& gpio_;
};
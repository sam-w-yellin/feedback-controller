#pragma once

#include <cstdint>
#include <optional>

#include "gpio_interface.hpp"

class SimulatedGpio : public Gpio
{
   public:
    SimulatedGpio(bool initial_state = false) : state_(initial_state) {}

    std::optional<std::string> Configure(Direction dir) final override;

    std::optional<std::string> Set(bool value) final override;

    std::expected<bool, std::string> Read() final override;

   private:
    bool state_;
    Direction direction_ = Direction::Input;
};

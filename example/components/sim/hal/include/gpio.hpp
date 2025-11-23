#pragma once

#include "gpio_interface.hpp"
#include <optional>
#include <cstdint>

class SimulatedGpio : public Gpio {
public:
    SimulatedGpio(bool initial_state = false)
        : state_(initial_state) {}

    // Configure GPIO (simulated always succeeds)
    std::optional<std::string> Configure(Direction dir) final override;
    // Set the gpio high or low
    std::optional<std::string> Set(bool value) final override;

    // Read the current state
    std::expected<bool, std::string> Read() final override;

private:
    bool state_;
    Direction direction_ = Direction::Input;
};

#include "gpio.hpp"
#include <optional>
#include <cstdint>

std::optional<std::string> SimulatedGpio::Configure(Direction dir) {
    direction_ = dir;
    return {};
};

std::optional<std::string> SimulatedGpio::Set(bool value){
    if (direction_ != Direction::Output) {
        return "GPIO is not configured as output";
    }
    state_ = value;
    return {};
};

std::expected<bool, std::string> SimulatedGpio::Read() {
    return state_;
};

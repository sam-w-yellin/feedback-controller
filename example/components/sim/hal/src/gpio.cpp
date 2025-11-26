#include "gpio.hpp"

#include <cstdint>

std::expected<void, std::string> SimulatedGpio::Configure(Direction dir)
{
    direction_ = dir;
    return {};
};

std::expected<void, std::string> SimulatedGpio::Set(bool value)
{
    if (direction_ != Direction::Output)
    {
        return std::unexpected("GPIO is not configured as output");
    }
    state_ = value;
    return {};
};

std::expected<bool, std::string> SimulatedGpio::Read()
{
    return state_;
};

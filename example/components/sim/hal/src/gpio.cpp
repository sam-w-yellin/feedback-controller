#include "gpio.hpp"

#include <cstdint>

std::expected<void, std::string_view> SimulatedGpio::Configure(Direction dir)
{
    direction_ = dir;
    return {};
};

std::expected<void, std::string_view> SimulatedGpio::Set(bool value)
{
    if (direction_ != Direction::Output)
    {
        return std::unexpected("GPIO is not configured as output");
    }
    state_ = value;
    return {};
};

std::expected<bool, std::string_view> SimulatedGpio::Read()
{
    return state_;
};

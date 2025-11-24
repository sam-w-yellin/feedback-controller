#pragma once

#include <expected>
#include <optional>
#include <string>

struct Gpio
{
    virtual ~Gpio() = default;

    enum Direction
    {
        Input,
        Output
    };

    virtual std::optional<std::string> Configure(Direction dir) = 0;

    virtual std::optional<std::string> Set(bool value) = 0;

    virtual std::expected<bool, std::string> Read() = 0;
};
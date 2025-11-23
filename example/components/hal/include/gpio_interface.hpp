#pragma once

#include <expected>
#include <optional>
#include <string>

struct Gpio {
    virtual ~Gpio() = default;

    enum Direction { Input, Output };

    // Configure the GPIO pin direction
    // Returns an error string if configuration fails
    virtual std::optional<std::string> Configure(Direction dir) = 0;

    // Set the pin output
    virtual std::optional<std::string> Set(bool value) = 0;

    // Read the pin input (if input)
    virtual std::expected<bool, std::string> Read() = 0;
};
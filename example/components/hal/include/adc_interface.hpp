#pragma once

#include <cstdint>
#include <expected>
#include <optional>
#include <string>

struct Adc
{
    virtual ~Adc() = default;

    // Configure the ADC hardware
    // Returns an error string if configuration fails
    virtual std::optional<std::string> Configure() = 0;

    // Read the raw ADC value
    // Returns either the raw value or an error string
    virtual std::expected<uint16_t, std::string> ReadRaw() = 0;
};
#pragma once

#include <cstdint>
#include <expected>
#include <string>

struct Adc
{
    virtual ~Adc() = default;

    virtual std::expected<void, std::string> Configure() = 0;

    virtual std::expected<uint16_t, std::string> ReadRaw() = 0;
};
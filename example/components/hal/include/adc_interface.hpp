#pragma once

#include <cstdint>
#include <expected>
#include <string>

struct Adc
{
    virtual ~Adc() = default;

    virtual std::expected<void, std::string_view> Configure() = 0;

    virtual std::expected<uint16_t, std::string_view> ReadRaw() = 0;
};
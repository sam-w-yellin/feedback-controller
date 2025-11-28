#include "adc.hpp"

std::expected<void, std::string_view> SimulatedAdc::Configure()
{
    return {};
}

std::expected<uint16_t, std::string_view> SimulatedAdc::ReadRaw()
{
    return raw_value_;
}

void SimulatedAdc::SetRawValue(uint16_t value)
{
    raw_value_ = value;
}
#include "adc.hpp"

std::optional<std::string> SimulatedAdc::Configure()
{
    return {};
}

std::expected<uint16_t, std::string> SimulatedAdc::ReadRaw()
{
    return raw_value_;
}

void SimulatedAdc::SetRawValue(uint16_t value)
{
    raw_value_ = value;
}
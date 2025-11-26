#pragma once

#include "adc_interface.hpp"
#include "feedback_controller_interface.hpp"

template <ControlLaw LAW, typename Converter>
struct AdcFeedback
{
    using Measurement = typename LAW::Measurement;
    using Raw = uint16_t;
    using State = std::pair<Measurement, Raw>;

    AdcFeedback(Adc& adc, Converter converter) : adc_(adc), Convert(converter) {}

    std::expected<std::pair<Measurement, State>, std::string> Read()
    {
        std::expected<Raw, std::string> maybe_raw = adc_.ReadRaw();
        if (!maybe_raw.has_value())
        {
            return std::unexpected(maybe_raw.error());
        }
        const auto& raw = maybe_raw.value();
        Measurement m = Convert(raw);
        return std::pair{m, std::pair{m, raw}};
    }

    std::expected<void, std::string> Configure()
    {
        const auto configure_result = adc_.Configure();
        if (!configure_result)
        {
            return std::unexpected(
                std::format("ADC configure failed: {}", configure_result.error()));
        }
        return {};
    }

    Converter Convert;
   private:
    Adc& adc_;
};
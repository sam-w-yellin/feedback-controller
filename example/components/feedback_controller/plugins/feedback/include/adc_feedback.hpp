#pragma once

#include "adc_interface.hpp"
#include "feedback_controller_interface.hpp"

template <ControlLaw LAW, auto Converter>
struct AdcFeedback
{
    using Measurement = typename LAW::Measurement;
    using Raw = uint16_t;
    using State = std::pair<Measurement, Raw>;

    AdcFeedback(Adc& adc) : adc_(adc) {}

    std::expected<std::pair<Measurement, State>, std::string_view> Read()
    {
        std::expected<Raw, std::string_view> maybe_raw = adc_.ReadRaw();
        if (!maybe_raw.has_value())
        {
            return std::unexpected(maybe_raw.error());
        }
        const auto& raw = maybe_raw.value();
        Measurement m = Convert(raw);
        return std::pair{m, std::pair{m, raw}};
    }

    std::expected<void, std::string_view> Configure()
    {
        const auto configure_result = adc_.Configure();
        if (!configure_result)
        {
            return std::unexpected(configure_result.error());
        }
        return {};
    }

    constexpr LAW::Measurement Convert(Raw raw)
    {
        return Converter(raw);
    };

   private:
    Adc& adc_;
};
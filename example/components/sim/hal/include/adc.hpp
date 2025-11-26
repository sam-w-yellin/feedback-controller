#include <cstdint>
#include <expected>
#include <string>

#include "adc_interface.hpp"

class SimulatedAdc : public Adc
{
   public:
    SimulatedAdc(uint16_t initial_value = 0) : raw_value_(initial_value) {}

    std::expected<void, std::string> Configure() final override;

    std::expected<uint16_t, std::string> ReadRaw() final override;

    void SetRawValue(uint16_t value);

   private:
    uint16_t raw_value_;
};

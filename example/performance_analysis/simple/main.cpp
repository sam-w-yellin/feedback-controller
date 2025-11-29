#include "adc.hpp"
#include "gpio.hpp"

void initialize_tec(Gpio& tec, Adc& thermocouple) {
    static_cast<void>(tec.Configure(Gpio::Output));
    static_cast<void>(thermocouple.Configure());
}

void step(Gpio& tec, Adc& thermocouple) {
    const auto raw_temp_adc = thermocouple.ReadRaw();
    const auto temp_uc = static_cast<float>(raw_temp_adc.value()) * 0.1f;

    if (temp_uc >= 80) {
        static_cast<void>(tec.Set(true));
    } else if (temp_uc <= 20) {
        static_cast<void>(tec.Set(false));
    }
}

int main() {
    SimulatedAdc thermocouple;
    SimulatedGpio tec;

    initialize_tec(tec, thermocouple);

    for (int i = 0; i < 100000000; i++) {
        step(tec, thermocouple);
    }
    return 0;
}
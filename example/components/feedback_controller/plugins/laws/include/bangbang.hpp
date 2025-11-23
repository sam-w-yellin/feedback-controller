#pragma once

#include "feedback_controller_interface.hpp"

struct BangBangLaw {
    using Measurement = int32_t;  // e.g., temperature in °C * 10
    using Command     = bool;     // on/off
    struct State {
        Command last_command{};
    };

    struct Config {
        Measurement min_threshold;
        Measurement max_threshold;
    };

    BangBangLaw(Measurement min_th, Measurement max_th) {
        config_.min_threshold = min_th;
        config_.max_threshold = max_th;
    }

    // Initialize the control law (returns initial state)
    std::expected<State, std::string> Initialize() {
        State s{};
        s.last_command = false; // start off
        return s;
    }

    // Compute next command and update state
    std::expected<std::pair<Command, State>, std::string> Compute(const Measurement& m) {
        if (m >= config_.max_threshold) {
            state_.last_command = true;
        } else if (m <= config_.min_threshold) {
            state_.last_command = false;
        }
        return std::make_pair(state_.last_command, state_);
    }

    State state_;
    Config config_;
};
#pragma once

#include "feedback_controller_interface.hpp"

struct BangBangRangeLaw
{
    using Measurement = int32_t;
    using Command = bool;
    struct State
    {
        Command last_command{};
    };

    struct Config
    {
        Measurement min_threshold;
        Measurement max_threshold;
    };

    BangBangRangeLaw(Measurement min_th, Measurement max_th)
    {
        config_.min_threshold = min_th;
        config_.max_threshold = max_th;
    }

    std::expected<State, std::string_view> Initialize()
    {
        State s{};
        s.last_command = false;
        return s;
    }

    std::expected<std::pair<Command, State>, std::string_view> Compute(const Measurement& m)
    {
        if (m >= config_.max_threshold)
        {
            state_.last_command = true;
        }
        else if (m <= config_.min_threshold)
        {
            state_.last_command = false;
        }
        return std::make_pair(state_.last_command, state_);
    }

    State state_;
    Config config_;
};
#pragma once

#include "feedback_controller_interface.hpp"

struct BangBangSetpointLaw
{
    using Measurement = int32_t;
    using Command = bool;
    struct State
    {
        Command last_command{};
    };

    struct Config
    {
        Measurement setpoint;
    };

    BangBangSetpointLaw(Measurement setpoint)
    {
        config_.setpoint = setpoint;
    }

    std::expected<State, std::string_view> Initialize()
    {
        State s{};
        s.last_command = false;
        return s;
    }

    std::expected<std::pair<Command, State>, std::string_view> Compute(const Measurement& m)
    {
        if (m >= config_.setpoint)
        {
            state_.last_command = true;
        }
        else
        {
            state_.last_command = false;
        }
        return std::make_pair(state_.last_command, state_);
    }

    State state_;
    Config config_;
};
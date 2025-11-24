#pragma once

#include <concepts>
#include <expected>
#include <format>
#include <optional>
#include <string>

template <typename FB, typename LAW, typename ACT>
struct ControllerState
{
    typename FB::State feedback_state;
    typename LAW::State control_state;
    typename ACT::State actuator_state;
};

template <typename C>
concept ControlLaw = requires(C law, const typename C::Measurement& m) {
    typename C::Measurement;
    typename C::Command;
    typename C::State;

    { law.Initialize() } -> std::same_as<std::expected<typename C::State, std::string>>;

    {
        law.Compute(m)
    }
    -> std::same_as<std::expected<std::pair<typename C::Command, typename C::State>, std::string>>;
};

template <typename FB, typename Law>
concept Feedback = ControlLaw<Law> && requires(FB fb) {
    typename FB::State;

    { fb.Configure() } -> std::same_as<std::optional<std::string>>;

    {
        fb.Read()
    } -> std::same_as<
        std::expected<std::pair<typename Law::Measurement, typename FB::State>, std::string>>;

    { fb.Convert(std::declval<typename FB::Raw>()) } -> std::same_as<typename Law::Measurement>;
};

template <typename AC, typename Law>
concept Actuator = ControlLaw<Law> && requires(AC ac, const typename Law::Command& cmd) {
    typename AC::State;

    { ac.Configure() } -> std::same_as<std::optional<std::string>>;

    { ac.Write(cmd) } -> std::convertible_to<std::expected<typename AC::State, std::string>>;

    { ac.Convert(std::declval<typename Law::Command>()) } -> std::same_as<typename AC::State>;
};

template <ControlLaw Law, Feedback<Law> FB, Actuator<Law> ACT>
class Controller
{
   public:
    using Measurement = typename Law::Measurement;
    using Command = typename Law::Command;

    Controller(FB& feedback, ACT& actuator, Law& law) : fb_(feedback), act_(actuator), law_(law) {}

    std::expected<typename Law::State, std::string> Initialize()
    {
        if (auto err = fb_.Configure()) return std::unexpected(*err);
        if (auto err = act_.Configure()) return std::unexpected(*err);
        auto law_state = law_.Initialize();
        if (!law_state.has_value()) return std::unexpected(law_state.error());
        return law_state.value();
    }

    std::expected<ControllerState<FB, Law, ACT>, std::string> Step()
    {
        auto fb_result = fb_.Read();
        if (!fb_result.has_value()) return std::unexpected(fb_result.error());
        auto [measurement, fb_state] = *fb_result;

        auto law_result = law_.Compute(measurement);
        if (!law_result.has_value()) return std::unexpected(law_result.error());
        auto [command, law_state] = *law_result;

        auto act_result = act_.Write(command);
        if (!act_result.has_value()) return std::unexpected(act_result.error());
        auto act_state = *act_result;

        ControllerState<FB, Law, ACT> state{
            .feedback_state = fb_state, .control_state = law_state, .actuator_state = act_state};
        return state;
    }

   private:
    FB& fb_;
    ACT& act_;
    Law& law_;
};

template <typename FB, typename LAW, typename ACT>
struct std::formatter<ControllerState<FB, LAW, ACT>>
{
    constexpr auto parse(std::format_parse_context& ctx)
    {
        return ctx.begin();
    }

    template <typename FormatContext>
    auto format(const ControllerState<FB, LAW, ACT>& s, FormatContext& ctx) const
    {
        return std::format_to(ctx.out(), "{{ feedback: {}, control: {}, actuator: {} }}",
                              to_string(s.feedback_state), to_string(s.control_state),
                              to_string(s.actuator_state));
    }
};
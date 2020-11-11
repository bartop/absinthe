#pragma once

#include "traits.hpp"
#include "parse_result.hpp"

#include <string>
#include <variant>
#include <utility>
#include <algorithm>

namespace absinthe
{

template<class Left, class Right>
class difference
{
public:
    template<class L, class R>
    constexpr difference(L&& l, R&& r) : 
        m_left_parser(std::forward<L>(l)),
        m_right_parser(std::forward<R>(r))
        {}

    using result_t = parser_result_t<Left>;

    template<class It>
    parse_result<It, result_t> parse(It begin, It end) const
    {
        auto [unused, result] = m_right_parser.parse(begin, end);
        (void) unused;
        auto parse_error = std::get_if<0>(&result);
        if (!parse_error)
            return {begin, "difference parser failed"};

        auto [result_it, second_result_variant] = m_left_parser.parse(begin, end);
        auto second_result = std::get_if<1>(&second_result_variant);
        if (!second_result) 
            return {begin, "error"};

        return {result_it, *second_result};
    }

private:
    Left m_left_parser;
    Right m_right_parser;
};

template<class L, class R>
difference(L&& l, R&& r) -> difference<std::decay_t<L>, std::decay_t<R>>;


template<
    class L,
    class R,
    std::enable_if_t<
        !std::is_convertible_v<L, std::string> &&
        !std::is_convertible_v<R, std::string>
    >* = nullptr
>
constexpr auto operator-(L&& l, R&& r) {
    return difference(std::forward<L>(l), std::forward<R>(r));
}

template<
    class L,
    class R,
    std::enable_if_t<
        !std::is_convertible_v<L, std::string> &&
        std::is_convertible_v<R, std::string>
    >* = nullptr
>
constexpr auto operator-(L&& l, R&& r) {
    return difference(std::forward<L>(l), string_(std::forward<R>(r)));
}

template<
    class L,
    class R,
    std::enable_if_t<
        std::is_convertible_v<L, std::string> &&
        !std::is_convertible_v<R, std::string>
    >* = nullptr
>
constexpr auto operator-(L&& l, R&& r) {
    return difference(string_(std::forward<L>(l)), std::forward<R>(r));
}

}

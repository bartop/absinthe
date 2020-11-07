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
class sequence
{
public:
    template<class L, class R>
    constexpr sequence(L&& l, R&& r) : 
        m_left_parser(std::forward<L>(l)),
        m_right_parser(std::forward<R>(r))
        {}

    using tuple_t = decltype(std::tuple_cat(
        std::declval<decltype(tuplize(std::declval<parser_result_t<Left>>()))>(), 
        std::declval<decltype(tuplize(std::declval<parser_result_t<Right>>()))>() 
    ));

    parse_result<std::string::const_iterator, tuple_t>
    parse(std::string::const_iterator begin, std::string::const_iterator end) const
    {
        auto [first_it, first_result_variant] = m_left_parser.parse(begin, end);
        auto first_result = std::get_if<1>(&first_result_variant);
        if (!first_result) 
            return {begin, std::get<0>(first_result_variant)};

        auto [second_it, second_result_variant] = m_right_parser.parse(first_it, end);
        auto second_result = std::get_if<1>(&second_result_variant);
        if (!second_result)
            return {begin, std::get<0>(second_result_variant)};

        return { second_it, std::tuple_cat(tuplize(*first_result), tuplize(*second_result)) };
    }

private:
    Left m_left_parser;
    Right m_right_parser;
};

template<class L, class R>
sequence(L&&, R&&) -> sequence<std::decay_t<L>, std::decay_t<R>>;

template<
    class L,
    class R,
    std::enable_if_t<
        !std::is_convertible_v<L, std::string> &&
        !std::is_convertible_v<R, std::string>
    >* = nullptr
>
constexpr auto operator>>(L&& left, R&& right)
{
    return sequence(std::forward<L>(left), std::forward<R>(right));
}

template<
    class L,
    class R,
    std::enable_if_t<
        std::is_convertible_v<L, std::string> &&
        !std::is_convertible_v<R, std::string>
    >* = nullptr
>
constexpr auto operator>>(L&& left, R&& right)
{
    return sequence(
        absinthe::string_(std::forward<L>(left)),
        std::forward<R>(right)
    );
}

template<
    class L,
    class R,
    std::enable_if_t<
        !std::is_convertible_v<L, std::string> &&
        std::is_convertible_v<R, std::string>
    >* = nullptr
>
constexpr auto operator>>(L&& left, R&& right)
{
    return sequence(
        std::forward<L>(left),
        absinthe::string_(std::forward<R>(right))
    );
}

}

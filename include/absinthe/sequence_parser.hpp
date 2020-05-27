#pragma once

#include "traits.hpp"

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
    sequence(L&& l, R&& r) : 
        m_left_parser(std::forward<L>(l)),
        m_right_parser(std::forward<R>(r))
        {}

    using tuple_t = decltype(std::tuple_cat(
        std::declval<decltype(tuplize(std::declval<parser_result_t<Left>>()))>(), 
        std::declval<decltype(tuplize(std::declval<parser_result_t<Right>>()))>() 
    ));

    std::pair<std::string::const_iterator, std::variant<std::string, tuple_t>>
    parse(std::string::const_iterator begin, std::string::const_iterator end) const
    {
        auto [first_it, first_result_variant] = m_left_parser.parse(begin, end);
        auto first_result = std::get_if<1>(&first_result_variant);
        if (!first_result) 
            return {begin, "error" };

        auto [second_it, second_result_variant] = m_right_parser.parse(first_it, end);
        auto second_result = std::get_if<1>(&second_result_variant);
        if (!second_result)
            return {begin, "error" };

        return { second_it, std::tuple_cat(tuplize(*first_result), tuplize(*second_result)) };
    }

private:
    Left m_left_parser;
    Right m_right_parser;
};

template<class Left, class Right>
auto make_sequence(Left&& left, Right&& right) 
{
    return sequence<std::decay_t<Left>, std::decay_t<Right>>(
        std::forward<Left>(left),
        std::forward<Right>(right)
    );
}

template<class Left, class Right>
auto operator>>(Left&& left, Right&& right)
{
    return make_sequence(
        std::forward<Left>(left),
        std::forward<Right>(right)
    );
}

}

#pragma once

#include "uint_parser.hpp"

#include <tuple>
#include <string>
#include <optional>
#include <utility>
#include <algorithm>

namespace absynth
{

template<class Parser>
using parser_tuple_t = 
    typename decltype(
        std::declval<Parser>().parse(std::string::const_iterator{}, std::string::const_iterator{})
    )::second_type::value_type;


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
        std::declval<parser_tuple_t<Left>>(), 
        std::declval<parser_tuple_t<Right>>()
    ));

    std::pair<std::string::const_iterator, std::optional<tuple_t>>
    parse(std::string::const_iterator begin, std::string::const_iterator end) const
    {
        auto [first_it, first_result] = m_left_parser.parse(begin, end);
        if (!first_result) 
            return {begin, std::nullopt };

        auto [second_it, second_result] = m_right_parser.parse(first_it, end);
        if (!second_result)
            return {begin, std::nullopt };

        return { second_it, std::tuple_cat(*first_result, *second_result) };
    }

private:
    Left m_left_parser;
    Right m_right_parser;
};

template<class Left, class Right>
auto make_sequence(Left&& left, Right&& right) {
    return sequence<std::decay_t<Left>, std::decay_t<Right>>(
        std::forward<Left>(left),
        std::forward<Right>(right)
    );
}

} // namespace absynth
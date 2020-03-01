
#pragma once

#include "traits.hpp"

#include <string>
#include <variant>
#include <utility>
#include <algorithm>

namespace absinthe
{

template<class Left, class Right>
class alternative
{
public:
    template<class L, class R>
    alternative(L&& l, R&& r) : 
        m_left_parser(std::forward<L>(l)),
        m_right_parser(std::forward<R>(r))
        {}

    using return_t = variant_sum_t<
        variantized_t<parser_result_t<Left>>,
        variantized_t<parser_result_t<Right>>
    >;

    std::pair<std::string::const_iterator, std::variant<std::string, return_t>>
    parse(std::string::const_iterator begin, std::string::const_iterator end) const
    {
        auto [first_it, first_result_variant] = m_left_parser.parse(begin, end);
        auto first_result = std::get_if<1>(&first_result_variant);
        if (first_result) 
            return {first_it, std::variant<std::string, return_t>(std::in_place_index<1>, *first_result) };

        auto [second_it, second_result_variant] = m_right_parser.parse(first_it, end);
        auto second_result = std::get_if<1>(&second_result_variant);
        if (second_result)
            return {second_it, std::variant<std::string, return_t>(std::in_place_index<1>, *second_result) };

        return {begin, std::variant<std::string, return_t>(std::in_place_index<0>, "error") };
    }

private:
    Left m_left_parser;
    Right m_right_parser;
};

template<class Left, class Right>
auto make_alternative(Left&& left, Right&& right) {
    return alternative<std::decay_t<Left>, std::decay_t<Right>>(
        std::forward<Left>(left),
        std::forward<Right>(right)
    );
}

} // namespace absinthe

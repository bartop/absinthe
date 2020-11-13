
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
class alternative
{
public:
    template<class L, class R>
    constexpr alternative(L&& l, R&& r) : 
        m_left_parser(std::forward<L>(l)),
        m_right_parser(std::forward<R>(r))
        {}

    using return_t = unwrap_single_element_pack_t<
        filter_duplicates_t<
            variant_sum_t<
                variantized_t<parser_result_t<Left>>,
                variantized_t<parser_result_t<Right>>
            >
        >
    >;

    template<class It>
    parse_result<It, return_t> parse(It begin, It end) const
    {
        auto [first_it, first_result_variant] = m_left_parser.parse(begin, end);
        auto first_result = std::get_if<1>(&first_result_variant);
        if (first_result) 
            return { first_it, *first_result };

        auto [second_it, second_result_variant] = m_right_parser.parse(first_it, end);
        auto second_result = std::get_if<1>(&second_result_variant);
        if (second_result) 
            return { second_it, *second_result };

        return {
            begin,
            parser_error{ "alternative parser failed - matched none of alternatives" }
        };
    }

private:
    Left m_left_parser;
    Right m_right_parser;
};

template<class L, class R>
alternative(L&& l, R&& r) -> alternative<std::decay_t<L>, std::decay_t<R>>;

template<
    class Left,
    class Right,
    std::enable_if_t<
        !std::is_convertible_v<Left, std::string> &&
        !std::is_convertible_v<Right, std::string>
    >* = nullptr
>
constexpr auto operator|(Left&& left, Right&& right)
{
    return alternative(std::forward<Left>(left), std::forward<Right>(right));
}

template<
    class Left,
    class Right,
    std::enable_if_t<
        std::is_convertible_v<Left, std::string> &&
        !std::is_convertible_v<Right, std::string>
    >* = nullptr
>
constexpr auto operator|(Left&& left, Right&& right)
{
    return alternative(
        absinthe::string_(std::forward<Left>(left)),
        std::forward<Right>(right)
    );
}

template<
    class Left,
    class Right,
    std::enable_if_t<
        !std::is_convertible_v<Left, std::string> &&
        std::is_convertible_v<Right, std::string>
    >* = nullptr
>
constexpr auto operator|(Left&& left, Right&& right)
{
    return alternative(
        std::forward<Left>(left),
        absinthe::string_(std::forward<Right>(right))
    );
}

}

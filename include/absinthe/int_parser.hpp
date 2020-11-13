#pragma once

#include "uint_parser.hpp"
#include "parse_result.hpp"

#include <variant>
#include <string>
#include <utility>
#include <algorithm>

namespace absinthe
{

class int_
{
    template<class It>
    parse_result<It, unsigned int> parse_unsigned(It begin, It end) const
    {
        return uint_{}.parse(begin, end);
    }

    template<class It>
    static int parse_sign(It &begin)
    {
        if (*begin != '-' && *begin != '+')
            return 1;

        return *begin++ == '+' ? 1 : -1;
    }

public:
    constexpr int_() noexcept = default;

    template<class It>
    parse_result<It, int> parse(It begin, It end) const
    {
        if (begin == end)
            return { begin, parser_error{"error parsing int - empty parsed range"} };

        int sign = parse_sign(begin);

        auto [it, result_variant] = parse_unsigned(begin, end);
        auto uint_result = std::get_if<1>(&result_variant);
        if (uint_result)
            return { it, static_cast<int>(*uint_result * sign) };
        else
            return { begin, parser_error{"error parsing int - empty parsed range"} };
    }
};

}

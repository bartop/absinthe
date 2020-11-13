#pragma once

#include "uint_parser.hpp"
#include "int_parser.hpp"
#include "parse_result.hpp"

#include <variant>
#include <string>
#include <utility>
#include <algorithm>
#include <cmath>

namespace absinthe
{

class double_
{
private:
    template<class It>
    int get_sign(It &begin) const
    {
        if (*begin != '+' && *begin != '-')
            return 1;

        return *begin++ == '+' ? 1 : -1;
    }

public:
    template<class It>
    parse_result<It, double> parse(It begin, It end) const
    {
        if (begin == end)
        {
            return {
                begin,
                parser_error{ "Error while parsing double - empty parsed range" }
            };
        }

        auto sign = get_sign(begin);
        auto [it, parsed_int_variant] = uint_().parse(begin, end);
        auto left_of_dot_value = std::get_if<unsigned>(&parsed_int_variant);
        if (!left_of_dot_value)
        {
            return {
                begin,
                parser_error{ "Error while parsing double - no double found in range" }
            };
        }

        double result = static_cast<long long>(*left_of_dot_value) * sign;

        if (it == end || *it != '.')
            return { it, result };

        ++it;
        auto [double_end_it, parsed_uint_variant] = uint_().parse(it, end);
        auto right_of_dot_value = std::get_if<unsigned>(&parsed_uint_variant);
        if (!right_of_dot_value)
            return { --it, result };

        double divisor = std::pow(10, std::distance(it, double_end_it));
        result += (static_cast<long long>(*right_of_dot_value) * sign) / divisor;

        return { double_end_it, result };
    }
};

}

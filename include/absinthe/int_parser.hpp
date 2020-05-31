#pragma once

#include "uint_parser.hpp"

#include <variant>
#include <string>
#include <utility>
#include <algorithm>

namespace absinthe
{

class int_
{
    std::pair<std::string::const_iterator, std::variant<std::string, unsigned>>
    parse_unsigned(std::string::const_iterator begin, std::string::const_iterator end) const
    {
        return uint_().parse(begin, end);
    }

    static int parse_sign(std::string::const_iterator &begin)
    {
        if (*begin != '-' && *begin != '+')
            return 1;

        return *begin++ == '+' ? 1 : -1;
    }

public:
    std::pair<std::string::const_iterator, std::variant<std::string, int>>
    parse(std::string::const_iterator begin, std::string::const_iterator end) const
    {
        if (begin == end)
            return {begin, "error"};

        int sign = parse_sign(begin);

        auto [it, result_variant] = parse_unsigned(begin, end);
        auto uint_result = std::get_if<1>(&result_variant);
        if (uint_result)
            return { it, static_cast<int>(*uint_result * sign) };
        else
            return { begin, "error" };
    }
};

}

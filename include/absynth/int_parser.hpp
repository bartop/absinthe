#pragma once

#include "uint_parser.hpp"

#include <tuple>
#include <string>
#include <optional>
#include <utility>
#include <algorithm>

namespace absynth
{
inline int parse_sign(std::string::const_iterator &begin);


class int_
{
    std::pair<std::string::const_iterator, std::optional<std::tuple<unsigned>>>
    parse_unsigned(std::string::const_iterator begin, std::string::const_iterator end) const
    {
        return uint_().parse(begin, end);
    }

public:
    std::pair<std::string::const_iterator, std::optional<std::tuple<int>>>
    parse(std::string::const_iterator begin, std::string::const_iterator end) const
    {
        if (begin == end)
            return {begin, std::nullopt};

        int sign = parse_sign(begin);

        auto [it, uint_result] = parse_unsigned(begin, end);
        if (uint_result)
            return { it, std::get<0>(*uint_result) * sign};
        else
            return { begin, std::nullopt };
    }
};

int parse_sign(std::string::const_iterator &begin)
{
    if (*begin != '-' && *begin != '+')
        return 1;

    return *begin++ == '+' ? 1 : -1;
}

} // namespace absynth
#pragma once

#include "uint_parser.hpp"
#include "int_parser.hpp"

#include <tuple>
#include <string>
#include <optional>
#include <utility>
#include <algorithm>
namespace absynth
{

class double_
{
private:
    int get_sign(std::string::const_iterator &begin) const
    {
        if (*begin != '+' && *begin != '-')
            return 1;

        return *begin++ == '+' ? 1 : -1;
    }

public:
    std::pair<std::string::const_iterator, std::optional<std::tuple<double>>>
    parse(std::string::const_iterator begin, std::string::const_iterator end) const
    {
        if (begin == end)
            return {begin, std::nullopt};

        auto sign = get_sign(begin);
        auto [it, parsed_int] = uint_().parse(begin, end);

        if (!parsed_int)
            return {begin, std::nullopt};

        auto left_of_dot_value = std::get<0>(*parsed_int);

        double result = static_cast<int>(left_of_dot_value) * sign;

        if (it == end || *it != '.')
            return {it, result};

        ++it;
        auto [double_end_it, parsed_unsigned] = uint_().parse(it, end);

        if (!parsed_unsigned)
            return {--it, result};

        auto right_of_dot_value = std::get<0>(*parsed_unsigned);
        double divisor = std::pow(10, (double_end_it - it));
        result += (static_cast<int>(right_of_dot_value) * sign) / divisor;
        return {double_end_it, result};
    }
};

} // namespace absynth
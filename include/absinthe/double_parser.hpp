#pragma once

#include "uint_parser.hpp"
#include "int_parser.hpp"

#include <variant>
#include <string>
#include <utility>
#include <algorithm>

namespace absinthe
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
    std::pair<std::string::const_iterator, std::variant<std::string,double>>
    parse(std::string::const_iterator begin, std::string::const_iterator end) const
    {
        if (begin == end)
            return {begin, "error"};

        auto sign = get_sign(begin);
        auto [it, parsed_int_variant] = uint_().parse(begin, end);
        auto left_of_dot_value = std::get_if<unsigned>(&parsed_int_variant);
        if (!left_of_dot_value)
            return {begin, "error"};

        double result = static_cast<long long>(*left_of_dot_value) * sign;

        if (it == end || *it != '.')
            return {it, result};

        ++it;
        auto [double_end_it, parsed_uint_variant] = uint_().parse(it, end);
        auto right_of_dot_value = std::get_if<unsigned>(&parsed_uint_variant);
        if (!right_of_dot_value)
            return {--it, result};

        double divisor = std::pow(10, (double_end_it - it));
        result += (static_cast<long long>(*right_of_dot_value) * sign) / divisor;

        return {double_end_it, result};
    }
};

} // namespace absinthe
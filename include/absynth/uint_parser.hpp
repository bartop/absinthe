#pragma once

#include <string>
#include <utility>
#include <optional>
#include <tuple>

namespace absynth
{

class uint_
{
public:
    std::pair<std::string::const_iterator, std::optional<std::tuple<unsigned>>>
    parse(std::string::const_iterator begin, std::string::const_iterator end) const
    {
        unsigned result = 0;
        auto it = begin;

        for (; it != end; ++it)
        {
            if (*it < '0' || *it > '9')
                break;

            result *= 10;
            result += *it - '0';
        }

        if (it == begin)
            return {begin, std::nullopt};

        return {it, result};
    }
};
} // namespace absynth

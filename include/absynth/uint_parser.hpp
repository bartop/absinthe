#pragma once

#include <string>
#include <utility>
#include <variant>

namespace absynth
{

class uint_
{
public:
    std::pair<std::string::const_iterator, std::variant<std::string, unsigned>>
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
            return {begin, "error"};

    return {it, result};
    }
};
} // namespace absynth

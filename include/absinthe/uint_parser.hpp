#pragma once

#include "parse_result.hpp"

namespace absinthe
{

class uint_
{
public:
    constexpr uint_() noexcept = default;

    template<class It>
    constexpr parse_result<It, unsigned> parse(It begin, It end) const
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
            return { begin, "Error while parsing uint - parsed range is empty" };

        return { it, result };
    }
};

}


#pragma once

#include "parse_result.hpp"

#include <string>
#include <variant>
#include <cctype>

namespace absinthe
{

class alnum
{
public:
    constexpr alnum() = default;

    template<class It>
    parse_result<It, char> parse(It begin, It end) const
    {
        if (begin == end || !std::isalnum(*begin))
            return { begin, parser_error{ "alnum parser failed" } };

        auto result = *begin;

        return { ++begin, result };
    }
};

}

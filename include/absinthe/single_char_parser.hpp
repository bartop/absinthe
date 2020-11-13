#pragma once

#include "parse_result.hpp"

#include <string>
#include <variant>

namespace absinthe
{

class single_char
{
public:
    constexpr single_char(char parsed) : m_parsed_char(parsed)
    { }

    template<class It>
    parse_result<It, char> parse(It begin, It end) const
    {
        if (begin == end || *begin != m_parsed_char)
            return { begin, parser_error{"error"} };

        return { ++begin, m_parsed_char };
    }

private:
    char m_parsed_char;
};

}

#pragma once

#include "parse_result.hpp"

#include <string>

namespace absinthe
{

class char_set
{
public:
    char_set(std::string parsed) : m_parsed_set(std::move(parsed))
    { }

    template<class It>
    parse_result<It, char> parse(It begin, It end) const
    {
        if (begin == end)
        {
            return {
                begin,
                parser_error{ "Char set parsing error - received empty range" }
            };
        }

        auto found = std::find(
            m_parsed_set.begin(),
            m_parsed_set.end(),
            *begin
        );
        if (found == m_parsed_set.end())
        {
            return {
                begin,
                parser_error{
                    "Char set parsing error - did not find any of chars in parsed range" 
                }
            };
        }

        return { ++begin, *found };
    }

private:
    std::string m_parsed_set;
};

}

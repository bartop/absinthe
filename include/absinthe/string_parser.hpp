#pragma once

#include "parse_result.hpp"

#include <tuple>
#include <algorithm>

namespace absinthe
{

class string_
{
public:
    string_(std::string parsed) : m_parsed_string(std::move(parsed))
    { }

    template<class It>
    parse_result<It, std::tuple<>> parse(It begin, It end) const
    {
        auto [parsed_it, input_it] = std::mismatch(
            m_parsed_string.begin(), m_parsed_string.end(),
            begin, end);

        if (parsed_it != m_parsed_string.end())
        {
            return {
                begin,
                parser_error{ "String literal parsing error - did not match string" }
            };
        }

        return {input_it, std::tuple<>{}};
    }

private:
    std::string m_parsed_string;
};

}

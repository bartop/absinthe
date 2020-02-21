#pragma once

#include "traits.hpp"

#include <vector>
#include <string>

namespace absynth
{
template <class Parser>
class repeated
{

public:
    using result_t = std::vector<parser_result_t<Parser>>;

    template <class T>
    repeated(T &&parser, int min_times = 0, int max_times = -1) : 
        m_parser(std::forward<T>(parser)),
        m_min_times(min_times),
        m_max_times(max_times)
    {
    }

    std::pair<std::string::const_iterator, std::variant<std::string, result_t>>
    parse(std::string::const_iterator begin, std::string::const_iterator end) const
    {
        result_t result;
        auto result_it = begin;
        parser_variant_t<Parser> parsed;
        while (true)
        {
            std::tie(result_it, parsed) = m_parser.parse(result_it, end);
            auto success_value = std::get_if<1>(&parsed);
            if (!success_value)            
                return { result_it, result };
            
            result.push_back(std::move(*success_value));
        }          

    }

private:

    Parser m_parser;
    int m_min_times;
    int m_max_times;
};
} // namespace absynth
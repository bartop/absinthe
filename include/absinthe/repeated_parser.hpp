#pragma once

#include "traits.hpp"

#include <vector>
#include <string>

namespace absinthe
{

template <class Parser>
class repeated
{
public:
    using result_t = std::vector<parser_result_t<Parser>>;

    template <class T>
    constexpr repeated(T &&parser, int min_times = 0, int max_times = -1) :
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

        for (int i = 0; !max_reached(i); ++i)
        {
            std::tie(result_it, parsed) = m_parser.parse(result_it, end);
            auto success_value = std::get_if<1>(&parsed);
            if (!success_value)
            {
                if (i < m_min_times)
                    return {begin, "error"};
                else
                    return {result_it, result};
            }

            result.push_back(std::move(*success_value));
        }
        return {result_it, result};
    }

private:
    Parser m_parser;
    int m_min_times;
    int m_max_times;

    bool max_reached(int i) const
    {
        return i >= m_max_times && m_max_times != -1;
    }
};

template<class T>
repeated(T&&, int, int) -> repeated<std::decay_t<T>>;

template<class Parser>
constexpr auto operator!(Parser&& parser)
{
    return repeated(std::forward<Parser>(parser), 0, 1);
}

}

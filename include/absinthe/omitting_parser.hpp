#pragma once

#include "traits.hpp"
#include "parse_result.hpp"

#include <string>
#include <variant>
#include <utility>
#include <algorithm>

namespace absinthe
{

template<class Parser>
class omit
{
public:
    template<class T>
    constexpr omit(T&& parser) : m_parser(std::forward<T>(parser)) {}

    template<class It>
    parse_result<It, std::tuple<>> parse(It begin, It end) const
    {
        auto [result_it, result_variant] = m_parser.parse(begin, end);
        if (std::get_if<1>(&result_variant))
            return {result_it, std::tuple<>{}};
        else
            return {begin, std::get<parser_error>(result_variant)};
    }

private:
    Parser m_parser;
};

template<class T>
omit(T&& parser) -> omit<std::decay_t<T>>;

}

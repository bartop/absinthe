#pragma once

#include "traits.hpp"

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

    std::pair<std::string::const_iterator, std::variant<std::string, std::tuple<>>>
    parse(std::string::const_iterator begin, std::string::const_iterator end) const
    {
        auto [result_it, result_variant] = m_parser.parse(begin, end);
        if (std::get_if<1>(&result_variant))
            return {result_it, std::tuple<>{}};
        else
            return {begin, "error"};
    }

private:
    Parser m_parser;
};

template<class T>
omit(T&& parser) -> omit<std::decay_t<T>>;

}

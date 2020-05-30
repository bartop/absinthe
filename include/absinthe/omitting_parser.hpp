#pragma once

#include "traits.hpp"

#include <string>
#include <variant>
#include <utility>
#include <algorithm>

namespace absinthe
{

template<class Parser>
class omitting_parser
{
public:
    template<class T>
    omitting_parser(T&& parser) : m_parser(std::forward<T>(parser)) {}

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
auto omit(T&& parser) {
    return omitting_parser<std::decay_t<T>>(std::forward<T>(parser));
}

}

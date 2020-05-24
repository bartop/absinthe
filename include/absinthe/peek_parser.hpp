#pragma once

#include "traits.hpp"

#include <string>
#include <variant>
#include <utility>
#include <algorithm>

namespace absinthe
{

template<class Parser>
class peek
{
public:
    template<class T>
    peek(T&& parser) : m_parser(std::forward<T>(parser)) {}

    using result_t = parser_result_t<Parser>;

    std::pair<std::string::const_iterator, std::variant<std::string, result_t>>
    parse(std::string::const_iterator begin, std::string::const_iterator end) const
    {
        auto [result_it, result_variant] = m_parser.parse(begin, end);
        (void) result_it;
        return {begin, result_variant};
    }

private:
    Parser m_parser;
};

template<class T>
auto make_peek(T&& parser)
{
    return peek<std::decay_t<T>>(std::forward<T>(parser));
}

}

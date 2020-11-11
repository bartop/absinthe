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
class optional
{
public:
    template<class T>
    constexpr optional(T&& parser) : m_parser(std::forward<T>(parser)) {}

    using return_t = std::optional<parser_result_t<Parser>>;

    template<class It>
    parse_result<It, return_t> parse(It begin, It end) const
    {
        auto [it, result_variant] = m_parser.parse(begin, end);
        auto result = std::get_if<1>(&result_variant);
        if (result)
            return { it, *result };
        else
            return { begin, std::nullopt };
    }

private:
    Parser m_parser;
};

template<class T>
optional(T&&) -> optional<std::decay_t<T>>;

template<
    class T,
    std::enable_if_t<!std::is_convertible_v<T, std::string>>* = nullptr
>
constexpr auto operator!(T&& parser)
{
    return optional(std::forward<T>(parser));
}

template<
    class T,
    std::enable_if_t<std::is_convertible_v<T, std::string>>* = nullptr
>
constexpr auto operator!(T&& str)
{
    return optional(string_(str));
}

}

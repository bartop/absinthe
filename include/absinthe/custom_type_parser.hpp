#pragma once

#include "traits.hpp"

#include <string>
#include <variant>
#include <utility>
#include <algorithm>

namespace absinthe
{

template<class Parser, class Function>
class custom_type
{
public:
    template<class T, class F>
    constexpr custom_type(
        T&& parser,
        F&& function
    ) : 
        m_parser(std::forward<T>(parser)),
        m_function(std::forward<F>(function)) {}

    using result_t = decltype(
        std::declval<Function>()(
            std::declval<parser_result_t<Parser>>()
        )
    );

    std::pair<std::string::const_iterator, std::variant<std::string, result_t>>
    parse(std::string::const_iterator begin, std::string::const_iterator end) const
    {
        auto [result_it, result_variant] = m_parser.parse(begin, end);
        auto result = std::get_if<1>(&result_variant);
        if (!result)
            return {
                begin,
                std::variant<std::string, result_t>(std::in_place_index<0>, "error")
            };
        return {
            result_it,
            std::variant<std::string, result_t>(
                std::in_place_index<1>,
                m_function(*result)
            )
        };
    }

private:
    Parser m_parser;
    Function m_function;
};

template<class T, class F>
custom_type(T&& parser, F&& transforming_function) ->
    custom_type<std::decay_t<T>, std::decay_t<F>>;

}

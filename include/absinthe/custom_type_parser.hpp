#pragma once

#include "traits.hpp"
#include "parse_result.hpp"

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

    template<class It>
    parse_result<It, result_t> parse(It begin, It end) const
    {
        auto [result_it, result_variant] = m_parser.parse(begin, end);
        auto result = std::get_if<1>(&result_variant);
        if (!result)
            return { begin, std::get<parser_error>(result_variant) };

        return { result_it, m_function(std::move(*result)) };
    }

private:
    Parser m_parser;
    Function m_function;
};

template<class T, class F>
custom_type(T&& parser, F&& transforming_function) ->
    custom_type<std::decay_t<T>, std::decay_t<F>>;

}

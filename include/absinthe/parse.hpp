#pragma once

#include "traits.hpp"

#include <string>
#include <utility>
#include <variant>

namespace absinthe
{

template <class It, class Parser>
auto parse(It it, It end, const Parser &parser)
{
    return parser.parse(it, end);
}

template <class Parsed, class Parser>
auto parse(const Parsed& str, const Parser &parser)
{
    return parse(std::begin(str), end(str), parser);
}

template <class It, class Parser>
parser_variant_t<Parser> strict_parse(It begin, It end, const Parser& parser)
{
    auto [it, result] = parser.parse(begin, end);
    if (it != end) {
        return parser_variant_t<Parser>(
            std::in_place_index<0>,
            "strict parse failed - did not consume whole input"
        );
    }
    return std::move(result);
}

template <class Parsed, class Parser>
parser_variant_t<Parser> strict_parse(const Parsed& parsed, const Parser& parser) 
{
    return strict_parse(std::begin(parsed), std::end(parsed), parser);
}

}

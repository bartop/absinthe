#pragma once

#include <string>

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
    return parser.parse(std::begin(str), end(str));
}

}

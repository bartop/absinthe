#pragma once

#include "single_char_parser.hpp"
#include "char_set_parser.hpp"

namespace absinthe
{

inline constexpr auto char_(char chr) {
    return single_char(chr);
}

inline auto char_(std::string chars_set) {
    return char_set(std::move(chars_set));
}

}

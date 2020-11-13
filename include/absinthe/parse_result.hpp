#pragma once

#include "parser_error.hpp"

#include <variant>
#include <string>
#include <utility>

namespace absinthe
{

template<class It, class Value>
using parse_result = std::pair<It, std::variant<parser_error, Value>>;

}

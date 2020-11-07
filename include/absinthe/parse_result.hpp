#pragma once

#include <variant>
#include <string>
#include <utility>

template<class It, class Value>
using parse_result = std::pair<It, std::variant<std::string, Value>>;

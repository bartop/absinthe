# absinthe - parser generator for `spirit` lovers 
## Overview

Absinthe is C++17 header-only library designed to allow creating type-safe parsers from within C++ code in most intuitive manner possbile. It is inspired and heavily influenced by `boost::spirit` library to allow simple and intuitive usage.

## Code sample - parsing custom rocord structure

```c++
#include <absinthe/int_parser.hpp>
#include <absinthe/custom_type_parser.hpp>
#include <absinthe/parse.hpp>

#include <tuple>

struct Record {
    int id;
    int value;
};

namespace ab = absinthe;

Record parseRecord(const std::string& to_parse)
{
    auto parser = ab::custom_type(
        "Record(id: " >> ab::int_{} >> ", value: " >> ab::int_{} >> ");",
        [] (std::tuple<int, int> parse_result) {
            return Record { std::get<0>(parse_result), std::get<1>(parse_result) };
        }
    );
    auto result = strict_parse(to_parse, parser);
    if (std::get_if<0>(&result) != nullptr)
        throw std::runtime_error(std::get<0>(result));

    return std::get<Record>(result);
}

```

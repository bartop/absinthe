# absinthe - parser generator for people used to `spirit`
## Overview

Absinthe is C++17 header-only library designed to allow creating type-safe parsers from within C++ code in most intuitive manner possbile. It is inspired and heavily influenced by `boost::spirit` library to allow simple and intuitive usage.

## Code sample - parsing rocord-like structure

```c++
struct Record {
    int id;
    int value;
};

namespace ab = absinthe;

Record parseRecord(const std::string& to_parse) {
    auto parser = ab::make_custom_parser(
        "Record(id: " >> ab::int_ >> ", value: " >> ab::int_ >> ");",
        [](std::tuple<int, int> parse_result) {
            return Record { std::get<0>(parse_result), std::get<1>(parse_result) };
        }
    );
}

```

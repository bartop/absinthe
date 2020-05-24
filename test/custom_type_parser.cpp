#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <absinthe/int_parser.hpp>
#include <absinthe/custom_type_parser.hpp>
#include <absinthe/parse.hpp>

#include <string>
#include <numeric>

struct test_type {
    int val;
};

TEST_CASE("custom type parser", "")
{
    using absinthe::make_custom_parser;
    using absinthe::int_;

    auto parser = make_custom_parser(
        int_(),
        [](auto val) { return test_type{val}; }
    );

    SECTION("parsing successful for matching input and result iterator is unmoved")
    {
        std::string input_string = GENERATE("1", "2", "10", "22");
        
        auto [result_it, parsing_result] =
            parser.parse(input_string.begin(), input_string.end());
        auto actual = std::get<1>(parsing_result);
        
        REQUIRE(result_it == input_string.end());
        REQUIRE(actual.val == std::stoi(input_string));
    }
}

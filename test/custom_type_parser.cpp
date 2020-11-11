#include <catch.hpp>

#include <absinthe/int_parser.hpp>
#include <absinthe/custom_type_parser.hpp>
#include <absinthe/parse.hpp>

#include <string>
#include <list>
#include <vector>
#include <numeric>

struct test_type {
    int val;
};

TEMPLATE_TEST_CASE(
    "custom type parser",
    "[parser][custom_type]",
    std::string, std::vector<char>, std::list<char>)
{
    using absinthe::custom_type;
    using absinthe::int_;

    auto parser = custom_type(
        int_(),
        [](auto val) { return test_type{val}; }
    );

    SECTION("parsing successful for matching input")
    {
        std::string basic_input = GENERATE("1", "2", "10", "22");
        auto input_string = TestType(basic_input.begin(), basic_input.end());
        
        auto [result_it, parsing_result] =
            parser.parse(input_string.begin(), input_string.end());
        auto actual = std::get<1>(parsing_result);
        
        REQUIRE(result_it == input_string.end());
        REQUIRE(actual.val == std::stoi(basic_input));
    }
}

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
        auto input_string = GENERATE(as<std::string>{}, "1", "2", "10", "22");
        auto input = TestType(input_string.begin(), input_string.end());
        
        auto [it, parsing_result] = parser.parse(input.begin(), input.end());
        auto actual = std::get<test_type>(parsing_result);
        
        REQUIRE(it == input.end());
        REQUIRE(actual.val == std::stoi(input_string));
    }
}

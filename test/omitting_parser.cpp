#include <catch.hpp>

#include <absinthe/int_parser.hpp>
#include <absinthe/omitting_parser.hpp>
#include <absinthe/parse.hpp>

#include <string>
#include <list>

TEMPLATE_TEST_CASE(
    "omitting parser",
    "[parser][omit_parser]",
    std::string, std::vector<char>, std::list<char>)
{
    using absinthe::omit;
    using absinthe::int_;

    auto parser = omit(int_());

    SECTION("parsing successful for matching input and result value is empty tuple")
    {
        std::string input_string = "128";
        auto input = TestType(input_string.begin(), input_string.end());
        
        auto [result_it, parsing_result] = parser.parse(input.begin(), input.end());
        auto actual = std::get<1>(parsing_result);
        
        REQUIRE(result_it == input.end());
        REQUIRE(std::is_same_v<decltype(actual), std::tuple<>>);
    }

    SECTION("parse failure for non matching input")
    {
        std::string input_string = GENERATE("a", ",asdf", "a1");
        auto input = TestType(input_string.begin(), input_string.end());

        auto [result_it, parsing_result] = parser.parse(input.begin(), input.end());
        auto error = std::get_if<0>(&parsing_result);
        
        REQUIRE(result_it == input.begin());
        REQUIRE(error != nullptr);
    }
}

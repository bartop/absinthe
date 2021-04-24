#include <catch2/catch.hpp>

#include <absinthe/int_parser.hpp>
#include <absinthe/omitting_parser.hpp>
#include <absinthe/parse.hpp>

#include <string>
#include <list>

TEMPLATE_TEST_CASE(
    "omitting parser",
    "[parser][omitting]",
    std::string, std::vector<char>, std::list<char>)
{
    using absinthe::omit;
    using absinthe::int_;

    auto parser = omit(int_());

    SECTION("parsing successful for matching input and result value is empty tuple")
    {
        auto input_string = GENERATE(as<std::string>{}, "128");
        auto input = TestType(input_string.begin(), input_string.end());
        
        auto [it, parsing_result] = parser.parse(input.begin(), input.end());
        auto actual = std::get<1>(parsing_result);
        
        REQUIRE(it == input.end());
        REQUIRE(std::is_same_v<decltype(actual), std::tuple<>>);
    }

    SECTION("parse failure for non matching input")
    {
        using absinthe::parser_error;
        std::string input_string = GENERATE("a", ",asdf", "a1");
        auto input = TestType(input_string.begin(), input_string.end());

        auto [it, parsing_result] = parser.parse(input.begin(), input.end());
        auto error = std::get_if<parser_error>(&parsing_result);
        
        REQUIRE(it == input.begin());
        REQUIRE(error != nullptr);
    }
}

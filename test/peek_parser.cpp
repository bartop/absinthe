#include <catch2/catch.hpp>

#include <absinthe/int_parser.hpp>
#include <absinthe/parse.hpp>
#include <absinthe/peek_parser.hpp>

#include <string>
#include <numeric>
#include <list>
#include <vector>

TEMPLATE_TEST_CASE(
    "peek parser",
    "[parser][peek_parser]",
    std::string, std::vector<char>, std::list<char>)
{
    using absinthe::peek;
    using absinthe::int_;

    auto parser = peek(int_());

    SECTION("parsing successful for matching input and result iterator is unmoved")
    {
        auto input_string = std::string{GENERATE("1", "2", "10", "22")};
        auto input = TestType(input_string.begin(), input_string.end());
        
        auto [result_it, parsing_result] = 
            parser.parse(input.begin(), input.end());
        auto actual = std::get<1>(parsing_result);
        
        REQUIRE(result_it == input.begin());
        REQUIRE(actual == std::stoi(input_string));
    }

    SECTION("parse failure for non matching input")
    {
        auto input_string = std::string{GENERATE("a", ",asdf", "a1")};
        auto input = TestType(input_string.begin(), input_string.end());

        auto [result_it, parsing_result] =
            parser.parse(input.begin(), input.end());
        auto error = std::get_if<0>(&parsing_result);
        
        REQUIRE(result_it == input.begin());
        REQUIRE(error != nullptr);
    }
}

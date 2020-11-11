#include <catch.hpp>

#include <absinthe/optional_parser.hpp>
#include <absinthe/string_parser.hpp>
#include <absinthe/parse.hpp>

#include <string>
#include <numeric>
#include <list>

TEMPLATE_TEST_CASE(
    "optional parser",
    "[parser][optional_parser]",
    std::string, std::vector<char>, std::list<char>)
{
    using absinthe::string_;
    using absinthe::optional;

    SECTION("optional parser parses single valid input")
    {
        auto parser = !string_("abc");

        auto input_string = std::string{"abc"};
        auto input = TestType(input_string.begin(), input_string.end());
        
        auto [result_it, parsing_result] =
            parser.parse(input.begin(), input.end());
        auto actual = std::get<1>(parsing_result);
        
        REQUIRE(std::tuple<>{} == actual);
        REQUIRE(result_it == input.end());
    }

    SECTION("optional parser parses invalid input as empty")
    {
        auto parser = !string_("abc");

        auto input_string = std::string{GENERATE("", "fdsdsfsd")};
        auto input = TestType(input_string.begin(), input_string.end());
        
        auto [result_it, parsing_result] =
            parser.parse(input.begin(), input.end());
        auto actual = std::get<1>(parsing_result);
        
        REQUIRE(std::nullopt == actual);
        REQUIRE(result_it == input.begin());
    }
}

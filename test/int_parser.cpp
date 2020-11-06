#include <catch.hpp>

#include <absinthe/int_parser.hpp>
#include <absinthe/parse.hpp>

#include <string>
#include <vector>
#include <list>

TEMPLATE_TEST_CASE(
    "any int parser",
    "[int][parser]",
    std::string, std::vector<char>, std::list<char>)
{
    auto any_int_parser = absinthe::int_();

    SECTION("parsing successful when input string matches a number")
    {
        auto input = GENERATE(
            as<std::string>{}, "314", "+314", "-314", "+314abc"
        );
        auto parseme = TestType(input.begin(), input.end());

        auto [result, parsed] = absinthe::parse(parseme, any_int_parser);
        REQUIRE(result != parseme.begin());
        REQUIRE(std::get<1>(parsed) == std::stoi(input));
    }

    SECTION("parsing fails when input string does not match a number")
    {
        std::string input = "bac3";
        auto parseme = TestType(input.begin(), input.end());
        
        auto [result, parsed] = absinthe::parse(parseme, any_int_parser);
        REQUIRE(result == parseme.begin());
        
        auto error = std::get_if<0>(&parsed);
        REQUIRE(error != nullptr);
    }

    SECTION("parsing fails when input string is empty")
    {
        std::string input;
        auto parseme = TestType(input.begin(), input.end());

        auto [result, parsed] = absinthe::parse(parseme, any_int_parser);
        REQUIRE(result == parseme.begin());
        
        auto error = std::get_if<0>(&parsed);
        REQUIRE(error != nullptr);
    }
}

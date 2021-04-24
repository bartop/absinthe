#include <catch2/catch.hpp>

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
            as<std::string>{}, "314", "+314", "-314", "+314abc");
        auto parseme = TestType(input.begin(), input.end());

        auto [it, parsed] = absinthe::parse(parseme, any_int_parser);
        REQUIRE(it != parseme.begin());
        REQUIRE(std::get<1>(parsed) == std::stoi(input));
    }

    SECTION("parsing fails when input string does not match a number")
    {
        using absinthe::parser_error;
        auto input = GENERATE(as<std::string>{}, "bac3", "");
        auto parseme = TestType(input.begin(), input.end());
        
        auto [it, parsed] = absinthe::parse(parseme, any_int_parser);
        REQUIRE(it == parseme.begin());
        
        auto error = std::get_if<parser_error>(&parsed);
        REQUIRE(error != nullptr);
    }
}

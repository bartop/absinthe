#include <catch.hpp>

#include <absinthe/char_parser.hpp>
#include <absinthe/parse.hpp>

#include <string>
#include <vector>
#include <list>

TEMPLATE_TEST_CASE(
    "char set parser",
    "[parser][single_char]",
    std::string, std::vector<char>, std::list<char>)
{
    auto parser = absinthe::char_("abc");

    SECTION("parser processes matching input")
    {
        auto input_str = 
            GENERATE(as<std::string>{}, "a", "b", "c", "asz", "bz", "ctrg");
        auto input = TestType(input_str.begin(), input_str.end());
        auto [it, result] = absinthe::parse(input, parser);
        REQUIRE(it == std::next(input.begin()));
        REQUIRE(std::get_if<char>(&result) != nullptr);
        REQUIRE(std::get<char>(result) == input.front());
    }

    SECTION("parser does not process matching input")
    {
        using absinthe::parser_error;
        auto input_str =
            GENERATE(as<std::string>{}, "f", "d", "e", "");
        auto input = TestType(input_str.begin(), input_str.end());
        auto [it, result] = absinthe::parse(input, parser);
        REQUIRE(it == input.begin());
        REQUIRE(std::get_if<parser_error>(&result) != nullptr);
    }
}

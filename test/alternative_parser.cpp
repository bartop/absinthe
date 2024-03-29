
#include <catch2/catch.hpp>

#include <absinthe/int_parser.hpp>
#include <absinthe/string_parser.hpp>
#include <absinthe/alternative_parser.hpp>
#include <absinthe/parse.hpp>

#include <string>
#include <list>
#include <vector>

TEMPLATE_TEST_CASE(
    "alternative (string | int) parser",
    "[parser][alternative]",
    std::string, std::vector<char>, std::list<char>)
{
    auto alternative_parser = "int-placeholder" | absinthe::int_();

    SECTION("parsing successful for first alternative")
    {
        std::string basic_input = GENERATE("int-placeholder 3.14", "int-placeholdergf");
        auto parser_input = TestType(basic_input.begin(), basic_input.end());
        auto [result_it, parsed] = parse(
            parser_input.begin(),
            parser_input.end(),
            alternative_parser
        );
        REQUIRE(result_it != parser_input.begin());
        auto value = std::get_if<1>(&parsed);
        REQUIRE(value != nullptr);
        REQUIRE(std::get_if<std::tuple<>>(value));
    }

    SECTION("parsing successful for second alternative")
    {
        std::string basic_input = GENERATE("3.14 5 asd", "121.4aaa");
        auto parser_input = TestType(basic_input.begin(), basic_input.end());
        auto [result_it, parsed] = parse(
            parser_input.begin(),
            parser_input.end(),
            alternative_parser
        );

        REQUIRE(result_it != parser_input.begin());
        auto value = std::get_if<1>(&parsed);
        REQUIRE(value != nullptr);
        REQUIRE(std::get_if<int>(value));
    }

    SECTION("parsing fails when input string is not fitting parser")
    {
        using absinthe::parser_error;
        auto basic_input = GENERATE(as<std::string>{}, "", "stuff", "aa", "int-p");
        auto parser_input = TestType(basic_input.begin(), basic_input.end());
        auto [result, parsed] = parse(
            parser_input.begin(),
            parser_input.end(),
            alternative_parser
        );

        REQUIRE(result == parser_input.begin());
        auto error = std::get_if<parser_error>(&parsed);
        REQUIRE(error != nullptr);
    }
}


TEMPLATE_TEST_CASE(
    "alternative (string | string) parser",
    "[parser][alternative]",
    std::string, std::vector<char>, std::list<char>)
{
    auto parser = absinthe::string_("placeholder") | "value";
    auto basic_input = GENERATE(as<std::string>{}, "value", "placeholderddd");
    auto parser_input = TestType(basic_input.begin(), basic_input.end());
    auto [result_it, parsed] = parse(
        parser_input.begin(),
        parser_input.end(),
        parser
    );

    REQUIRE(result_it != parser_input.begin());
    auto value = std::get_if<1>(&parsed);
    REQUIRE(value != nullptr);
    REQUIRE(*value == std::tuple<>{});
}

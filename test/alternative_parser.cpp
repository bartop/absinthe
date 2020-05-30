
#define CATCH_CONFIG_MAIN

#include <catch.hpp>

#include <absinthe/int_parser.hpp>
#include <absinthe/string_parser.hpp>
#include <absinthe/alternative_parser.hpp>
#include <absinthe/parse.hpp>

#include <string>

TEST_CASE("alternative parser", "string | int")
{
    auto alternative_parser = absinthe::string_("int-placeholder") | absinthe::int_();

    SECTION("parsing successful for first alternative")
    {
        std::string parser_input = GENERATE("int-placeholder 3.14", "int-placeholdergf");
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
        std::string parser_input = GENERATE("3.14 5 asd", "121.4aaa");
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
        std::string parser_input = GENERATE("stuff", "aa", "int-p");
        auto [result, parsed] = parse(
            parser_input.begin(),
            parser_input.end(),
            alternative_parser
        );

        REQUIRE(result == parser_input.begin());
        auto error = std::get_if<std::string>(&parsed);
        REQUIRE(error != nullptr);
    }

    SECTION("parsing fails when input string is empty")
    {
        std::string parser_input;
        auto [result, parsed] = parse(
            parser_input.begin(),
            parser_input.end(),
            alternative_parser
        );

        REQUIRE(result == parser_input.begin());
        auto error = std::get_if<std::string>(&parsed);
        REQUIRE(error != nullptr);
    }
}

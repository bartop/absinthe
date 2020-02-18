#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <absynth/int_parser.hpp>
#include <absynth/parse.hpp>

#include <string>

TEST_CASE("any int parser", "")
{
    auto any_int_parser = absynth::int_();

    SECTION("parsing successful when input string matches a number")
    {
        auto expected = int();
        auto parser_input = std::string();

        SECTION("input string is positive number")
        {
            expected = 314;
            parser_input = std::to_string(expected);
        }
        SECTION("input string has leading zeros")
        {
            expected = 314;
            parser_input = "000" + std::to_string(expected);
        }
        SECTION("input string has leading +")
        {
            expected = 314;
            parser_input = "+" + std::to_string(expected);
        }
        SECTION("expected number is negative")
        {
            expected = -314;
            parser_input = std::to_string(expected);
        }
        SECTION("longer input string sucessfully matched")
        {
            expected = 314;
            parser_input = std::to_string(expected) + "abc";
        }

        auto [result, parsed] = absynth::parse(parser_input.begin(), parser_input.end(), any_int_parser);
        REQUIRE(result != parser_input.begin());
        REQUIRE(std::get<0>(parsed) == expected);
    }

    SECTION("parsing fails when input string does not match a number")
    {
        std::string parser_input = "bac3";
        auto [result, parsed] = absynth::parse(parser_input.begin(), parser_input.end(), any_int_parser);
        REQUIRE(result == parser_input.begin());
        REQUIRE(std::get<0>(parsed) == std::nullopt);
    }

    SECTION("parsing fails when input string is empty")
    {
        std::string parser_input;
        auto [result, parsed] = absynth::parse(parser_input.begin(), parser_input.end(), any_int_parser);
        REQUIRE(result == parser_input.begin());
        REQUIRE(std::get<0>(parsed) == std::nullopt);
    }
}

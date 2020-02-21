#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <absynth/double_parser.hpp>
#include <absynth/parse.hpp>

#include <string>

TEST_CASE("any int parser", "")
{
    auto any_int_parser = absynth::double_();

    SECTION("parsing successful when input string matches a number")
    {
        auto expected = double();
        auto parser_input = std::string();

        SECTION("input string is positive number")
        {
            expected = 3.14;
            parser_input = std::to_string(expected);
        }
        SECTION("input string has leading +")
        {
            expected = 3.14;
            parser_input = "+" + std::to_string(expected);
        }
        SECTION("expected number is negative")
        {
            expected = -3.14;
            parser_input = std::to_string(expected);
        }

        SECTION("longer input string sucessfully matched")
        {
            expected = 3.14;
            parser_input = "+" + std::to_string(expected) + "abc";

        }

        SECTION("input string ending with dot")
        {
            expected = 3;
            parser_input = "3.";

        }

        auto [result, parsed] = absynth::parse(parser_input.begin(), parser_input.end(), any_int_parser);
        REQUIRE(result != parser_input.begin());
        REQUIRE(std::get<double>(parsed) == Approx(expected));
    }

    SECTION("parsing fails when input string does not match a number")
    {
        std::string parser_input = "bac3.12";
        auto [result, parsed] = absynth::parse(parser_input.begin(), parser_input.end(), any_int_parser);
        REQUIRE(result == parser_input.begin());

		auto error = std::get_if<std::string>(&parsed);
		REQUIRE(error != nullptr);
    }

    SECTION("parsing fails when input string is empty")
    {
        std::string parser_input;
        auto [result, parsed] = absynth::parse(parser_input.begin(), parser_input.end(), any_int_parser);
        REQUIRE(result == parser_input.begin());

		auto error = std::get_if<std::string>(&parsed);
		REQUIRE(error != nullptr);
    }
}

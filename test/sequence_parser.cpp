#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <absynth/double_parser.hpp>
#include <absynth/string_parser.hpp>
#include <absynth/sequence_parser.hpp>
#include <absynth/parse.hpp>

#include <string>

TEST_CASE("sequence parser", "")
{
    SECTION("parsing successful")
    {
        std::string parser_input = "double: 3.14";
        auto sequence_parser = absynth::make_sequence(absynth::string_("double: "), absynth::double_());

        auto [result, parsed] = absynth::parse(parser_input.begin(), parser_input.end(), sequence_parser);
        REQUIRE(result != parser_input.begin());
        (void) parsed;
        // REQUIRE(std::get<0>(parsed) == Approx(expected));
    }

    SECTION("parsing fails when input string is empty")
    {
        std::string parser_input;
        auto sequence_parser = absynth::make_sequence(absynth::string_("double: "), absynth::double_());
        auto [result, parsed] = absynth::parse(parser_input.begin(), parser_input.end(), sequence_parser);
        REQUIRE(result == parser_input.begin());
        (void) parsed;
        // REQUIRE(std::get<0>(parsed) == std::nullopt);
    }
}

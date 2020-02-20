#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <absynth/double_parser.hpp>
#include <absynth/string_parser.hpp>
#include <absynth/sequence_parser.hpp>
#include <absynth/parse.hpp>

#include <string>

TEST_CASE("sequence parser", "")
{
    auto sequence_parser = absynth::make_sequence(absynth::string_("double: "), absynth::double_());

    SECTION("parsing successful")
    {
        std::string parser_input = GENERATE("double: 3.14", "double: 3.14 5 asd", "double: 3.14aaa");
        auto [result_it, parsed] = absynth::parse(parser_input.begin(), parser_input.end(), sequence_parser);

        REQUIRE(result_it != parser_input.begin());
        REQUIRE(std::get<0>(*parsed) == "double: ");
        REQUIRE(std::get<1>(*parsed) == Approx(3.14));
    }

    SECTION("parsing fails when input string is empty")
    {
        std::string parser_input;
        auto [result, parsed] = absynth::parse(parser_input.begin(), parser_input.end(), sequence_parser);

        REQUIRE(result == parser_input.begin());
        REQUIRE(parsed == std::nullopt);
    }

    SECTION("parsing fails when input string matches only a part of declared pattern")
    {
        std::string parser_input = "double: ";
        auto [result, parsed] = absynth::parse(parser_input.begin(), parser_input.end(), sequence_parser);

        REQUIRE(result == parser_input.begin());
        REQUIRE(parsed == std::nullopt);
    }

}

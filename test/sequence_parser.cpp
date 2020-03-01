#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <absinthe/double_parser.hpp>
#include <absinthe/string_parser.hpp>
#include <absinthe/sequence_parser.hpp>
#include <absinthe/parse.hpp>

#include <string>

TEST_CASE("sequence parser", "")
{
    auto sequence_parser = absinthe::make_sequence(absinthe::string_("double: "), absinthe::double_());

    SECTION("parsing successful")
    {
        std::string parser_input = GENERATE("double: 3.14", "double: 3.14 5 asd", "double: 3.14aaa");
        auto [result_it, parsed] = absinthe::parse(parser_input.begin(), parser_input.end(), sequence_parser);

        REQUIRE(result_it != parser_input.begin());
        REQUIRE(std::get<std::string>(std::get<1>(parsed)) == "double: ");
        REQUIRE(std::get<double>(std::get<1>(parsed)) == Approx(3.14));
    }

    SECTION("parsing fails when input string is empty")
    {
        std::string parser_input;
        auto [result, parsed] = absinthe::parse(parser_input.begin(), parser_input.end(), sequence_parser);

        REQUIRE(result == parser_input.begin());
        auto error = std::get_if<std::string>(&parsed);
        REQUIRE(error != nullptr);
    }

    SECTION("parsing fails when input string matches only a part of declared pattern")
    {
        std::string parser_input = "double: ";
        auto [result, parsed] = absinthe::parse(parser_input.begin(), parser_input.end(), sequence_parser);

	REQUIRE(result == parser_input.begin());
	auto error = std::get_if<std::string>(&parsed);
        REQUIRE(error != nullptr);
        }

}

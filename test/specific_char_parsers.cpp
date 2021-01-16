#include <catch.hpp>

#include <absinthe/char_parser.hpp>
#include <absinthe/parse.hpp>

#include <string>
#include <vector>
#include <list>

TEMPLATE_TEST_CASE(
    "specific char parsers",
    "[parser][char]",
    std::string, std::vector<char>, std::list<char>)
{
	auto parser = absinthe::alnum{};

	SECTION("parser accepts matching input string")
	{
		auto input_string = GENERATE(as<std::string>{}, "a", "R", "3");
        auto input = TestType(input_string.begin(), input_string.end());

		auto [it, parsed] = parse(input, parser);

		REQUIRE(it == ++input.begin());
		REQUIRE(std::get<char>(parsed) == input_string.front());
	}
	
	SECTION("parser does not accept not matching input string")
	{
        using absinthe::parser_error;
		auto input_string = GENERATE(as<std::string>{}, "[", "", "&");
        auto input = TestType(input_string.begin(), input_string.end());

		auto [it, parsed] = parse(input, parser);

		REQUIRE(it == input.begin());

		auto error = std::get_if<parser_error>(&parsed);
		REQUIRE(error != nullptr);
	}
}

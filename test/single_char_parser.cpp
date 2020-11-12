#include <catch.hpp>

#include <absinthe/char_parser.hpp>
#include <absinthe/parse.hpp>

#include <string>
#include <vector>
#include <list>

TEMPLATE_TEST_CASE(
    "single char parser",
    "[parser][char]",
    std::string, std::vector<char>, std::list<char>)
{
	auto parser = absinthe::char_('a');

	SECTION("parser matches input string")
	{
		std::string input = "a";
        auto parseme = TestType(input.begin(), input.end());
		auto [result, parsed] = absinthe::parse(parseme, parser);
		REQUIRE(result == parseme.end());
		REQUIRE(std::get<char>(parsed) == 'a');
	}
	
	SECTION("parser does not match input string")
	{
		std::string input = "b";
        auto parseme = TestType(input.begin(), input.end());
		auto [result, parsed] = absinthe::parse(parseme, parser);
		REQUIRE(result == parseme.begin());
		auto error = std::get_if<std::string>(&parsed);
		REQUIRE(error != nullptr);
	}

	SECTION("parser fails to parse empty input string")
	{
		std::string input;
        auto parseme = TestType(input.begin(), input.end());
		auto [result, parsed] = absinthe::parse(parseme, parser);
		REQUIRE(result == parseme.begin());
		
		auto error = std::get_if<std::string>(&parsed);
		REQUIRE(error != nullptr);
	}

	SECTION("longer input string sucessfully matched")
	{
		std::string input = "ab";
        auto parseme = TestType(input.begin(), input.end());
		auto [result, parsed] = absinthe::parse(parseme, parser);
		REQUIRE(result == ++parseme.begin());
		REQUIRE(std::get<char>(parsed) == 'a');
	}	
}

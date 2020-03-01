
#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <absinthe/single_char_parser.hpp>
#include <absinthe/parse.hpp>

#include <string>

TEST_CASE("single char parser", "")
{
	auto char_parser = absinthe::char_('a');

	SECTION("parser matches input string")
	{
		std::string parseme = "a";
		auto [result, parsed] = absinthe::parse(parseme.begin(), parseme.end(), char_parser);
		REQUIRE(result == parseme.end());
		REQUIRE(std::get<char>(parsed) == 'a');
	}
	
	SECTION("parser does not match input string")
	{
		std::string parseme = "b";
		auto [result, parsed] = absinthe::parse(parseme.begin(), parseme.end(), char_parser);
		REQUIRE(result == parseme.begin());
		auto error = std::get_if<std::string>(&parsed);
		REQUIRE(error != nullptr);
	}

	SECTION("parser fails to parse empty input string")
	{
		std::string parseme;
		auto [result, parsed] = absinthe::parse(parseme.begin(), parseme.end(), char_parser);
		REQUIRE(result == parseme.begin());
		
		auto error = std::get_if<std::string>(&parsed);
		REQUIRE(error != nullptr);
	}

	SECTION("longer input string sucessfully matched")
	{
		std::string parseme = "ab";
		auto [result, parsed] = absinthe::parse(parseme.begin(), parseme.end(), char_parser);
		REQUIRE(result == ++parseme.begin());
		REQUIRE(std::get<char>(parsed) == 'a');
	}	
}


#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <absynth/single_char_parser.hpp>
#include <absynth/parse.hpp>

#include <string>

TEST_CASE("single char parser", "")
{
	auto char_parser = absynth::char_('a');

	SECTION("parser matches input string")
	{
		std::string parseme = "a";
		auto [result, parsed] = absynth::parse(parseme.begin(), parseme.end(), char_parser);
		REQUIRE(result == parseme.end());
		REQUIRE(std::get<0>(parsed) == 'a');
	}
	
	SECTION("parser does not match input string")
	{
		std::string parseme = "b";
		auto [result, parsed] = absynth::parse(parseme.begin(), parseme.end(), char_parser);
		REQUIRE(result == parseme.begin());
		REQUIRE(std::get<0>(parsed) == std::nullopt);
	}

	SECTION("parser fails to parse empty input string")
	{
		std::string parseme;
		auto [result, parsed] = absynth::parse(parseme.begin(), parseme.end(), char_parser);
		REQUIRE(result == parseme.begin());
		REQUIRE(std::get<0>(parsed) == std::nullopt);
	}

	SECTION("longer input string sucessfully matched")
	{
		std::string parseme = "ab";
		auto [result, parsed] = absynth::parse(parseme.begin(), parseme.end(), char_parser);
		REQUIRE(result == ++parseme.begin());
		REQUIRE(std::get<0>(parsed) == 'a');
	}	
}

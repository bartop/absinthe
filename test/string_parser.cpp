
#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <absynth/string_parser.hpp>
#include <absynth/parse.hpp>

#include <string>

TEST_CASE("string literal parser", "")
{
	auto string_parser = absynth::string_("abc");

	SECTION("parser matches input string")
	{
		std::string parseme = "abc";
		auto [result, parsed] = absynth::parse(parseme.begin(), parseme.end(), string_parser);
		REQUIRE(result == parseme.end());
		REQUIRE(std::get<0>(*parsed) == "abc");
	}
	
	SECTION("parser does not match input string")
	{
		std::string parseme = "bac";
		auto [result, parsed] = absynth::parse(parseme.begin(), parseme.end(), string_parser);
		REQUIRE(result == parseme.begin());
		REQUIRE(parsed == std::nullopt);
	}

	SECTION("parser fails to parse empty input string")
	{
		std::string parseme;
		auto [result, parsed] = absynth::parse(parseme.begin(), parseme.end(), string_parser);
		REQUIRE(result == parseme.begin());
		REQUIRE(parsed == std::nullopt);
	}

	SECTION("longer input string sucessfully matched")
	{
		std::string parseme = "abcccdsds";
		auto [result, parsed] = absynth::parse(parseme.begin(), parseme.end(), string_parser);
		REQUIRE(result == parseme.begin() + std::get<0>(*parsed).size());
		REQUIRE(std::get<0>(*parsed) == "abc");
	}	
}

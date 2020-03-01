
#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <absinthe/string_parser.hpp>
#include <absinthe/parse.hpp>

#include <string>

TEST_CASE("string literal parser", "")
{
	auto string_parser = absinthe::string_("abc");

	SECTION("parser matches input string")
	{
		std::string parseme = "abc";
		auto [result, parsed] = absinthe::parse(parseme.begin(), parseme.end(), string_parser);
		REQUIRE(result == parseme.end());
		REQUIRE(std::get<1>(parsed) == "abc");
	}
	
	SECTION("parser does not match input string")
	{
		std::string parseme = "bac";
		auto [result, parsed] = absinthe::parse(parseme.begin(), parseme.end(), string_parser);
		REQUIRE(result == parseme.begin());
		REQUIRE(std::get<0>(parsed) == "error");
	}

	SECTION("parser fails to parse empty input string")
	{
		std::string parseme;
		auto [result, parsed] = absinthe::parse(parseme.begin(), parseme.end(), string_parser);
		REQUIRE(result == parseme.begin());
		REQUIRE(std::get<0>(parsed) == "error");
	}

	SECTION("longer input string sucessfully matched")
	{
		std::string parseme = "abcccdsds";
		auto [result, parsed] = absinthe::parse(parseme.begin(), parseme.end(), string_parser);
		REQUIRE(result == parseme.begin() + std::get<1>(parsed).size());
		REQUIRE(std::get<1>(parsed) == "abc");
	}	
}

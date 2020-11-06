#include <catch.hpp>

#include <absinthe/string_parser.hpp>
#include <absinthe/parse.hpp>

#include <string>
#include <vector>
#include <list>

TEMPLATE_TEST_CASE(
    "string literal parser",
    "[parser][string]",
    std::string, std::vector<char>, std::list<char>)
{
	auto string_parser = absinthe::string_("abc");

	SECTION("parser matches input string")
	{
		std::string parseme = "abc";
        auto to_parse = TestType(parseme.begin(), parseme.end());
		auto [result, parsed] = absinthe::parse(to_parse, string_parser);
		REQUIRE(result == to_parse.end());
		REQUIRE(std::get<1>(parsed) == std::tuple<>{});
	}
	
	SECTION("parser does not match input string")
	{
		std::string parseme = "bac";
        auto to_parse = TestType(parseme.begin(), parseme.end());
		auto [result, parsed] = absinthe::parse(to_parse, string_parser);
		REQUIRE(result == to_parse.begin());
		REQUIRE(std::get<0>(parsed) == "failed to parse string");
	}

	SECTION("parser fails to parse empty input string")
	{
		std::string parseme;
        auto to_parse = TestType(parseme.begin(), parseme.end());
		auto [result, parsed] = absinthe::parse(to_parse, string_parser);
		REQUIRE(result == to_parse.begin());
		REQUIRE(std::get<0>(parsed) == "failed to parse string");
	}

	SECTION("longer input string sucessfully matches")
	{
		std::string parseme = "abcccdsds";
        auto to_parse = TestType(parseme.begin(), parseme.end());
		auto [result, parsed] = absinthe::parse(to_parse, string_parser);
		REQUIRE(result != to_parse.begin());
		REQUIRE(result != to_parse.end());
		REQUIRE(std::get<1>(parsed) == std::tuple<>{});
	}	
}

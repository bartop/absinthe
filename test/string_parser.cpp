#include <catch2/catch.hpp>

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
    using absinthe::parser_error;
    auto pattern = std::string{"abc"};
	auto string_parser = absinthe::string_(pattern);

	SECTION("parser matches input string")
	{
		auto parseme = std::string{GENERATE("abc", "abcccdsds")};
        auto to_parse = TestType(parseme.begin(), parseme.end());
		auto [it, parsed] = parse(to_parse, string_parser);
		REQUIRE(it == std::next(to_parse.begin(), pattern.size()));
		REQUIRE(std::get<1>(parsed) == std::tuple<>{});
	}
	
	SECTION("parser does not match input string")
	{
		auto parseme = std::string{GENERATE("bac", "")};
        auto to_parse = TestType(parseme.begin(), parseme.end());
		auto [it, parsed] = parse(to_parse, string_parser);
		REQUIRE(it == to_parse.begin());
		REQUIRE(std::get<parser_error>(parsed).message() ==
            "String literal parsing error - did not match string");
	}
}

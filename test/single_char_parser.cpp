#include <catch2/catch.hpp>

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
    using absinthe::parser_error;
	auto parser = absinthe::char_('a');

	SECTION("parser accepts matching input string")
	{
		auto input_string = std::string{GENERATE("a", "ab", "ac")};
        auto input = TestType(input_string.begin(), input_string.end());
		auto [it, parsed] = parse(input, parser);
		REQUIRE(it == ++input.begin());
		REQUIRE(std::get<char>(parsed) == 'a');
	}
	
	SECTION("parser does not accept not matching input string")
	{
		auto input_string = std::string{GENERATE("b", "")};
        auto input = TestType(input_string.begin(), input_string.end());
		auto [it, parsed] = parse(input, parser);
		REQUIRE(it == input.begin());
		auto error = std::get_if<parser_error>(&parsed);
		REQUIRE(error != nullptr);
	}
}

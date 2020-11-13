#include <catch.hpp>

#include <absinthe/double_parser.hpp>
#include <absinthe/parse.hpp>

#include <vector>
#include <deque>
#include <string>

TEMPLATE_TEST_CASE(
    "any double parser",
    "[parser][double]",
    std::string, std::vector<char>, std::deque<char>
)
{
    auto double_parser = absinthe::double_();

    SECTION("parsing successful when input string matches a number")
    {
        auto input = GENERATE(
            as<std::string>{}, "3.14", "+3.14", "-3.14", "+3.14abc", "3."
        );
        auto parseme = TestType(input.begin(), input.end());

        auto [result, parsed] = absinthe::parse(parseme, double_parser);
        REQUIRE(result != parseme.begin());
        REQUIRE(std::get<double>(parsed) == Approx(std::stod(input)));
    }

    SECTION("parsing fails when input string does not match a number")
    {
        using absinthe::parser_error;
        auto input = GENERATE(as<std::string>{}, "bac3.12", "");
        auto parseme = TestType(input.begin(), input.end());
        auto [result, parsed] = absinthe::parse(parseme, double_parser);
        REQUIRE(result == parseme.begin());

		auto error = std::get_if<parser_error>(&parsed);
		REQUIRE(error != nullptr);
    }
}

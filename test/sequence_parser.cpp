#include <catch.hpp>

#include <absinthe/double_parser.hpp>
#include <absinthe/string_parser.hpp>
#include <absinthe/sequence_parser.hpp>
#include <absinthe/parse.hpp>

#include <string>
#include <vector>
#include <list>

TEMPLATE_TEST_CASE(
    "sequence parser",
    "[parser][sequence]",
    std::string, std::vector<char>, std::list<char>)
{
    auto sequence_parser = "double: " >> absinthe::double_();

    SECTION("parsing successful")
    {
        auto input_string = std::string{GENERATE(
            "double: 3.14",
            "double: 3.14 5 asd",
            "double: 3.14aaa"
        )};
        auto input = TestType(input_string.begin(), input_string.end());
        auto [result_it, parsed] =
            parse(input.begin(), input.end(), sequence_parser);

        REQUIRE(result_it != input.begin());
        REQUIRE(std::get<double>(std::get<1>(parsed)) == Approx(3.14));
    }

    SECTION("parsing fails when input string is empty")
    {
        auto input = TestType{};
        auto [result, parsed] = 
            absinthe::parse(input.begin(), input.end(), sequence_parser);

        REQUIRE(result == input.begin());
        auto error = std::get_if<std::string>(&parsed);
        REQUIRE(error != nullptr);
    }

    SECTION("parsing fails when input string matches only a part of declared pattern")
    {
        auto input_string = std::string{"double: "};
        auto input = TestType(input_string.begin(), input_string.end());
        auto [result, parsed] = parse(input.begin(), input.end(), sequence_parser);

        REQUIRE(result == input.begin());
        auto error = std::get_if<std::string>(&parsed);
        REQUIRE(error != nullptr);
    }

}

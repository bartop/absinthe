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

    SECTION("parsing successful when string matches parser")
    {
        auto number = GENERATE(as<std::string>{}, "3.14", "5.12", "3");
        SECTION(number) 
        {
            auto input_string = "double: " + number;
            auto input = TestType(input_string.begin(), input_string.end());
            auto [it, parsed] =
                parse(input.begin(), input.end(), sequence_parser);

            REQUIRE(it == input.end());
            REQUIRE(std::get<double>(std::get<1>(parsed)) == Approx(std::stod(number)));
        }
    }

    SECTION("parsing successful when string start matches parser")
    {
        auto input_string = GENERATE(
            as<std::string>{},
            "double: 3.14 5 asd",
            "double: 3.14aaa"
        );
        auto input = TestType(input_string.begin(), input_string.end());
        auto [it, parsed] =
            parse(input.begin(), input.end(), sequence_parser);

        REQUIRE(it != input.begin());
        REQUIRE(std::get<double>(std::get<1>(parsed)) == Approx(3.14));
    }

    SECTION("parsing fails when input string does not match full pattern")
    {
        using absinthe::parser_error;
        auto input_string = GENERATE(as<std::string>{}, "", "double: ");
        auto input = TestType{input_string.begin(), input_string.end()};
        auto [it, parsed] = 
            absinthe::parse(input.begin(), input.end(), sequence_parser);

        REQUIRE(it == input.begin());
        auto error = std::get_if<parser_error>(&parsed);
        REQUIRE(error != nullptr);
    }
}

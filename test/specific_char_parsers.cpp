#include <catch.hpp>

#include <absinthe/char_parser.hpp>
#include <absinthe/parse.hpp>

#include <string>
#include <vector>
#include <list>

TEMPLATE_TEST_CASE(
    "specific char parsers",
    "[parser][char]",
    std::string, std::vector<char>, std::list<char>)
{
    SECTION("alnum parser")
    {
        auto parser = absinthe::alnum{};

        SECTION("parser accepts matching input string")
        {
            auto input_string = GENERATE(as<std::string>{}, "a", "R", "3");
            auto input = TestType(input_string.begin(), input_string.end());

            auto [it, parsed] = parse(input, parser);

            REQUIRE(it == ++input.begin());
            REQUIRE(std::get<char>(parsed) == input_string.front());
        }
        
        SECTION("parser does not accept not matching input string")
        {
            using absinthe::parser_error;
            auto input_string = GENERATE(as<std::string>{}, "[", "", "&");
            auto input = TestType(input_string.begin(), input_string.end());

            auto [it, parsed] = parse(input, parser);

            REQUIRE(it == input.begin());

            auto error = std::get_if<parser_error>(&parsed);
            REQUIRE(error != nullptr);
        }
    }

    SECTION("blank parser")
    {
        auto parser = absinthe::blank{};

        SECTION("parser accepts matching input string")
        {
            auto input_string = GENERATE(as<std::string>{}, " ", "\t");
            auto input = TestType(input_string.begin(), input_string.end());

            auto [it, parsed] = parse(input, parser);

            REQUIRE(it == ++input.begin());
            REQUIRE(std::get<char>(parsed) == input_string.front());
        }
        
        SECTION("parser does not accept not matching input string")
        {
            using absinthe::parser_error;
            auto input_string = GENERATE(as<std::string>{}, "", "\n", "1", "[", "a", "&");
            auto input = TestType(input_string.begin(), input_string.end());

            auto [it, parsed] = parse(input, parser);

            REQUIRE(it == input.begin());

            auto error = std::get_if<parser_error>(&parsed);
            REQUIRE(error != nullptr);
        }
    }

    SECTION("alpha parser")
    {
        auto parser = absinthe::alpha{};

        SECTION("parser accepts matching input string")
        {
            auto input_string = GENERATE(as<std::string>{}, "a", "R", "g");
            auto input = TestType(input_string.begin(), input_string.end());

            auto [it, parsed] = parse(input, parser);

            REQUIRE(it == ++input.begin());
            REQUIRE(std::get<char>(parsed) == input_string.front());
        }
        
        SECTION("parser does not accept not matching input string")
        {
            using absinthe::parser_error;
            auto input_string = GENERATE(as<std::string>{}, "1", "[", "", "&");
            auto input = TestType(input_string.begin(), input_string.end());

            auto [it, parsed] = parse(input, parser);

            REQUIRE(it == input.begin());

            auto error = std::get_if<parser_error>(&parsed);
            REQUIRE(error != nullptr);
        }
    }
}

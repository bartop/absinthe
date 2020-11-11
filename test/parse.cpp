#include <catch.hpp>

#include <absinthe/int_parser.hpp>
#include <absinthe/string_parser.hpp>
#include <absinthe/alternative_parser.hpp>
#include <absinthe/parse.hpp>

#include <string>
#include <list>
#include <vector>

TEMPLATE_TEST_CASE(
    "parse and strict parse tests",
    "[parse][strict_parse]",
    std::string, std::vector<char>, std::list<char>)
{
    auto parser = absinthe::int_{};

    SECTION("full match")
    {
        auto str = std::string{GENERATE("1214", "463", "221")};

        auto input = TestType(str.begin(), str.end());

        SECTION("parse succeeds with full match")
        {
            auto [it, result] = parse(input, parser);
            REQUIRE(it == input.end());
            REQUIRE(std::get_if<0>(&result) == nullptr);
        }

        SECTION("strict_parse succeeds with full match")
        {
            auto result = strict_parse(input, parser);
            REQUIRE(std::get_if<0>(&result) == nullptr);
        }
    }

    SECTION("not full match")
    {
        auto str = std::string{
            GENERATE("1214fdsfd", "463es", "221-")};

        auto input = TestType(str.begin(), str.end());

        SECTION("parse succeeds without full match")
        {
            auto [it, result] = parse(input, parser);
            REQUIRE(it != input.end());
            REQUIRE(std::get_if<0>(&result) == nullptr);
        }

        SECTION("strict_parse fails without full match")
        {
            auto result = strict_parse(input, parser);
            REQUIRE(std::get_if<0>(&result) != nullptr);
        }
    }
}

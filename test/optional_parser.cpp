#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <absinthe/optional_parser.hpp>
#include <absinthe/string_parser.hpp>
#include <absinthe/parse.hpp>

#include <string>
#include <numeric>

TEST_CASE("optional parser", "")
{
    using absinthe::string_;
    using absinthe::optional;

    SECTION("optional parser parses single valid input")
    {
        auto parser = !string_("abc");

        auto input = std::string{"abc"};
        
        auto [result_it, parsing_result] =
            parser.parse(input.begin(), input.end());
        auto actual = std::get<1>(parsing_result);
        
        REQUIRE(std::tuple<>{} == actual);
        REQUIRE(result_it == input.end());
    }

    SECTION("optional parser parses invalid input as empty")
    {
        auto parser = !string_("abc");

        auto input = std::string{"fdsdsfsd"};
        
        auto [result_it, parsing_result] =
            parser.parse(input.begin(), input.end());
        auto actual = std::get<1>(parsing_result);
        
        REQUIRE(std::nullopt == actual);
        REQUIRE(result_it == input.begin());
    }

    SECTION("optional parser parses empty input")
    {
        auto parser = !string_("abc");

        auto input = std::string{};
        
        auto [result_it, parsing_result] =
            parser.parse(input.begin(), input.end());
        auto actual = std::get<1>(parsing_result);
        
        REQUIRE(std::nullopt == actual);
        REQUIRE(result_it == input.begin());
    }
}

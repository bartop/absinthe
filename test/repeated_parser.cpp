#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <absinthe/string_parser.hpp>
#include <absinthe/repeated_parser.hpp>
#include <absinthe/string_parser.hpp>
#include <absinthe/parse.hpp>

#include <string>
#include <numeric>

std::string concat_vector(const std::vector<std::string>& strings)
{
    return std::accumulate(strings.begin(), strings.end(), std::string{});
}

TEST_CASE("repeated parser", "")
{
    using absinthe::string_;
    using absinthe::repeated;

    SECTION("parsing successful")
    {
        auto parser = repeated(string_("abc"), 0, 3);

        std::vector<std::string> input = GENERATE(
            std::vector<std::string>{3, "abc"},
            std::vector<std::string>{2, "abc"},
            std::vector<std::string>{1, "abc"},
            std::vector<std::string>{}
        );

        std::string input_string = concat_vector(input);
        
        auto [result_it, parsing_result] = parser.parse(input_string.begin(), input_string.end());
        auto actual = std::get<1>(parsing_result);
        
        (void) result_it;
        REQUIRE(std::vector<std::tuple<>>(input.size()) == actual);
    }

    SECTION("reapeted parser works as optional parser")
    {
        auto parser = !string_("abc");

        std::vector<std::string> input = GENERATE(
            std::vector<std::string>{1, "abc"},
            std::vector<std::string>{}
        );

        std::string input_string = concat_vector(input);
        
        auto [result_it, parsing_result] = parser.parse(input_string.begin(), input_string.end());
        auto actual = std::get<1>(parsing_result);
        
        (void) result_it;
        REQUIRE(std::vector<std::tuple<>>(input.size()) == actual);
    }

    SECTION("parsing fails when matched too few repeated values")
    {
        auto parser = repeated(string_("abc"), 3, 4);
        std::string input_string = GENERATE("abc", "abcabc");
        
        auto [result_it, parsing_result] = parser.parse(input_string.begin(), input_string.end());
        auto error = std::get_if<std::string>(&parsing_result);

        (void) result_it;
        REQUIRE(error != nullptr);
    }

    SECTION("parser does not consume values above specified limit")
    {
        auto parser = repeated(string_("abc"), 1, 2);
        std::string input_string = "abcabcabcabc";

        auto [result_it, parsing_result ] = parser.parse(input_string.begin(), input_string.end());
        auto actual = std::get<1>(parsing_result);
        
        (void) result_it;
        REQUIRE(actual.size() == 2);
    }
}
    

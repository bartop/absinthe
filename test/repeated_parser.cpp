#include <catch.hpp>

#include <absinthe/repeated_parser.hpp>
#include <absinthe/string_parser.hpp>
#include <absinthe/parse.hpp>

#include <string>
#include <numeric>
#include <list>

std::string concat_vector(const std::vector<std::string>& strings)
{
    return std::accumulate(strings.begin(), strings.end(), std::string{});
}

TEMPLATE_TEST_CASE(
    "repeated parser",
    "[parser][repeated]",
    std::string, std::vector<char>, std::list<char>)
{
    using absinthe::string_;
    using absinthe::repeated;

    SECTION("parsing successful on valid input")
    {
        auto parser = repeated(string_("abc"), 0, 3);

        auto input = GENERATE(
            std::vector<std::string>{3, "abc"},
            std::vector<std::string>{2, "abc"},
            std::vector<std::string>{1, "abc"},
            std::vector<std::string>{}
        );

        auto input_string = concat_vector(input);
        auto in_bytes = TestType(input_string.begin(), input_string.end());
        
        auto [it, parsing_result] =
            parser.parse(in_bytes.begin(), in_bytes.end());
        auto actual = std::get<1>(parsing_result);
        
        REQUIRE(it == in_bytes.end());
        REQUIRE(std::vector<std::tuple<>>(input.size()) == actual);
    }

    SECTION("parsing fails when matched too few repeated values")
    {
        using absinthe::parser_error;
        auto parser = repeated(string_("abc"), 3, 4);
        auto input_string = GENERATE(as<std::string>{}, "abc", "abcabc");
        
        auto [it, parsing_result] =
            parser.parse(input_string.begin(), input_string.end());
        auto error = std::get_if<parser_error>(&parsing_result);

        (void) it;
        REQUIRE(error != nullptr);
    }

    SECTION("parser does not consume values above specified limit")
    {
        auto parser = repeated(string_("abc"), 1, 2);
        auto input_string = std::string{"abcabcabcabc"};

        auto [result_it, parsing_result] =
            parser.parse(input_string.begin(), input_string.end());
        auto actual = std::get<1>(parsing_result);
        
        (void) result_it;
        REQUIRE(actual.size() == 2);
    }
}

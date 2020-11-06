#include <catch.hpp>

#include <absinthe/string_parser.hpp>
#include <absinthe/omitting_parser.hpp>
#include <absinthe/parse.hpp>

#include <string>
#include <numeric>

TEST_CASE("omit parser", "")
{
    using absinthe::omit;
    using absinthe::string_;

    auto parser = omit(string_("string"));

    SECTION("parsing successful for matching input and result value is empty tuple")
    {
        std::string input_string = "string";
        
        auto [result_it, parsing_result] =
            parser.parse(input_string.begin(), input_string.end());
        auto actual = std::get<1>(parsing_result);
        
        REQUIRE(result_it == input_string.end());
        REQUIRE(std::is_same_v<decltype(actual), std::tuple<>>);
    }

    SECTION("parse failure for non matching input")
    {
        std::string input_string = GENERATE("a", ",asdf", "a1");

        auto [result_it, parsing_result] = parser.parse(
            input_string.begin(),
            input_string.end()
        );
        auto error = std::get_if<0>(&parsing_result);
        
        REQUIRE(result_it == input_string.begin());
        REQUIRE(error != nullptr);
    }
}

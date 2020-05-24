#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <absinthe/int_parser.hpp>
#include <absinthe/parse.hpp>
#include <absinthe/peek_parser.hpp>

#include <string>
#include <numeric>

TEST_CASE("peek parser", "")
{
    using absinthe::make_peek;
    using absinthe::int_;

    auto parser = make_peek(int_());

    SECTION("parsing successful for matching input and result iterator is unmoved")
    {
        std::string input_string = GENERATE("1", "2", "10", "22");
        
        auto [result_it, parsing_result] =
            parser.parse(input_string.begin(), input_string.end());
        auto actual = std::get<1>(parsing_result);
        
        REQUIRE(result_it == input_string.begin());
        REQUIRE(actual == std::stoi(input_string));
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

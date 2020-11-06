#include <catch.hpp>

#include <absinthe/string_parser.hpp>
#include <absinthe/int_parser.hpp>
#include <absinthe/parse.hpp>
#include <absinthe/difference_parser.hpp>

#include <string>
#include <numeric>

TEST_CASE("difference parser", "")
{
    using absinthe::difference;
    using absinthe::string_;
    using absinthe::int_;

    auto parser = int_() - "11";

    SECTION("parsing successful for matching input")
    {
        std::string input_string = GENERATE("1", "2", "10", "22");
        
        auto [result_it, parsing_result] =
            parser.parse(input_string.begin(), input_string.end());
        auto actual = std::get<1>(parsing_result);
        
        REQUIRE(result_it == input_string.end());
        REQUIRE(actual == std::stoi(input_string));
    }

    SECTION("parse failure for input matching negative part")
    {
        std::string input_string = GENERATE("11");
        
        auto [result_it, parsing_result] =
            parser.parse(input_string.begin(), input_string.end());
        auto error = std::get_if<0>(&parsing_result);
        
        REQUIRE(error != nullptr);
        REQUIRE(result_it == input_string.begin());
    }
}

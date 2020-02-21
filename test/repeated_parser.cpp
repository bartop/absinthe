#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <absynth/string_parser.hpp>
#include <absynth/repeated_parser.hpp>
#include <absynth/string_parser.hpp>
#include <absynth/parse.hpp>

#include <string>
#include <numeric>

std::string concat_vector(const std::vector<std::string>& strings)
{
    return std::accumulate(strings.begin(), strings.end(), std::string{});
}

TEST_CASE("repeated parser", "")
{
    using absynth::repeated;
    using absynth::string_;

    auto parser = repeated<absynth::string_>(string_("abc"), 0, 3);
    

    SECTION("parsing successful")
    {
        std::vector<std::string> expected_result = GENERATE(
            std::vector<std::string>{3, "abc"},
            std::vector<std::string>{2, "abc"},
            std::vector<std::string>{1, "abc"},
            std::vector<std::string>{}
        );

        std::string input_string = concat_vector(expected_result);
        
        auto [result_it, parsing_result] = parser.parse(input_string.begin(), input_string.end());
        auto actual = std::get<1>(parsing_result);
        
        (void) result_it;
        REQUIRE(expected_result == actual);
    }
}
    
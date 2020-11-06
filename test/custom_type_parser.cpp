#include <catch.hpp>

#include <absinthe/int_parser.hpp>
#include <absinthe/custom_type_parser.hpp>
#include <absinthe/parse.hpp>

#include <string>
#include <numeric>

struct test_type {
    int val;
};

TEST_CASE("custom type parser", "")
{
    using absinthe::custom_type;
    using absinthe::int_;

    auto parser = custom_type(
        int_(),
        [](auto val) { return test_type{val}; }
    );

    SECTION("parsing successful for matching input and result iterator is unmoved")
    {
        std::string input_string = GENERATE("1", "2", "10", "22");
        
        auto [result_it, parsing_result] =
            parser.parse(input_string.begin(), input_string.end());
        auto actual = std::get<1>(parsing_result);
        
        REQUIRE(result_it == input_string.end());
        REQUIRE(actual.val == std::stoi(input_string));
    }
}

#include <catch2/catch.hpp>

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

    SECTION("cntrl parser")
    {
        auto parser = absinthe::cntrl{};

        SECTION("parser accepts matching input string")
        {
            auto input_string = GENERATE(as<std::string>{}, "\01", "\02", "\010");
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

    SECTION("digit parser")
    {
        auto parser = absinthe::digit{};

        SECTION("parser accepts matching input string")
        {
            auto input_string = GENERATE(as<std::string>{}, "1", "2", "0");
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

    SECTION("graph parser")
    {
        auto parser = absinthe::graph{};

        SECTION("parser accepts matching input string")
        {
            auto input_string = GENERATE(as<std::string>{}, "&", "[", "1", "2", "0");
            auto input = TestType(input_string.begin(), input_string.end());

            auto [it, parsed] = parse(input, parser);

            REQUIRE(it == ++input.begin());
            REQUIRE(std::get<char>(parsed) == input_string.front());
        }
        
        SECTION("parser does not accept not matching input string")
        {
            using absinthe::parser_error;
            auto input_string = GENERATE(as<std::string>{}, "", "\0", "\1", "\2", " ", "\n");
            auto input = TestType(input_string.begin(), input_string.end());

            auto [it, parsed] = parse(input, parser);

            REQUIRE(it == input.begin());

            auto error = std::get_if<parser_error>(&parsed);
            REQUIRE(error != nullptr);
        }
    }

    SECTION("print parser")
    {
        auto parser = absinthe::print{};

        SECTION("parser accepts matching input string")
        {
            auto input_string = GENERATE(as<std::string>{}, "&", "[", "1", "2", "0", " ");
            auto input = TestType(input_string.begin(), input_string.end());

            auto [it, parsed] = parse(input, parser);

            REQUIRE(it == ++input.begin());
            REQUIRE(std::get<char>(parsed) == input_string.front());
        }
        
        SECTION("parser does not accept not matching input string")
        {
            using absinthe::parser_error;
            auto input_string = GENERATE(as<std::string>{}, "", "\0", "\1", "\2", "\n");
            auto input = TestType(input_string.begin(), input_string.end());

            auto [it, parsed] = parse(input, parser);

            REQUIRE(it == input.begin());

            auto error = std::get_if<parser_error>(&parsed);
            REQUIRE(error != nullptr);
        }
    }

    SECTION("punct parser")
    {
        auto parser = absinthe::punct{};

        SECTION("parser accepts matching input string")
        {
            auto input_string = GENERATE(as<std::string>{}, "&", "!", ".", ",");
            auto input = TestType(input_string.begin(), input_string.end());

            auto [it, parsed] = parse(input, parser);

            REQUIRE(it == ++input.begin());
            REQUIRE(std::get<char>(parsed) == input_string.front());
        }
        
        SECTION("parser does not accept not matching input string")
        {
            using absinthe::parser_error;
            auto input_string = GENERATE(as<std::string>{}, "", "\0", "\1", "\2", "\n");
            auto input = TestType(input_string.begin(), input_string.end());

            auto [it, parsed] = parse(input, parser);

            REQUIRE(it == input.begin());

            auto error = std::get_if<parser_error>(&parsed);
            REQUIRE(error != nullptr);
        }
    }

    SECTION("space parser")
    {
        auto parser = absinthe::space{};

        SECTION("parser accepts matching input string")
        {
            auto input_string = GENERATE(as<std::string>{}, " ", "\n", "\t");
            auto input = TestType(input_string.begin(), input_string.end());

            auto [it, parsed] = parse(input, parser);

            REQUIRE(it == ++input.begin());
            REQUIRE(std::get<char>(parsed) == input_string.front());
        }
        
        SECTION("parser does not accept not matching input string")
        {
            using absinthe::parser_error;
            auto input_string = GENERATE(as<std::string>{}, "", "a", ".", "2", "V");
            auto input = TestType(input_string.begin(), input_string.end());

            auto [it, parsed] = parse(input, parser);

            REQUIRE(it == input.begin());

            auto error = std::get_if<parser_error>(&parsed);
            REQUIRE(error != nullptr);
        }
    }

    SECTION("xdigit parser")
    {
        auto parser = absinthe::xdigit{};

        SECTION("parser accepts matching input string")
        {
            auto input_string = GENERATE(as<std::string>{}, "1", "4", "a", "F");
            auto input = TestType(input_string.begin(), input_string.end());

            auto [it, parsed] = parse(input, parser);

            REQUIRE(it == ++input.begin());
            REQUIRE(std::get<char>(parsed) == input_string.front());
        }
        
        SECTION("parser does not accept not matching input string")
        {
            using absinthe::parser_error;
            auto input_string = GENERATE(as<std::string>{}, "", "R", ".", "!", "\2");
            auto input = TestType(input_string.begin(), input_string.end());

            auto [it, parsed] = parse(input, parser);

            REQUIRE(it == input.begin());

            auto error = std::get_if<parser_error>(&parsed);
            REQUIRE(error != nullptr);
        }
    }

    SECTION("lower parser")
    {
        auto parser = absinthe::lower{};

        SECTION("parser accepts matching input string")
        {
            auto input_string = GENERATE(as<std::string>{}, "a", "s", "d", "f");
            auto input = TestType(input_string.begin(), input_string.end());

            auto [it, parsed] = parse(input, parser);

            REQUIRE(it == ++input.begin());
            REQUIRE(std::get<char>(parsed) == input_string.front());
        }
        
        SECTION("parser does not accept not matching input string")
        {
            using absinthe::parser_error;
            auto input_string = GENERATE(as<std::string>{}, "", "R", ".", "!", "\2");
            auto input = TestType(input_string.begin(), input_string.end());

            auto [it, parsed] = parse(input, parser);

            REQUIRE(it == input.begin());

            auto error = std::get_if<parser_error>(&parsed);
            REQUIRE(error != nullptr);
        }
    }

    SECTION("upper parser")
    {
        auto parser = absinthe::upper{};

        SECTION("parser accepts matching input string")
        {
            auto input_string = GENERATE(as<std::string>{}, "A", "S", "D", "F");
            auto input = TestType(input_string.begin(), input_string.end());

            auto [it, parsed] = parse(input, parser);

            REQUIRE(it == ++input.begin());
            REQUIRE(std::get<char>(parsed) == input_string.front());
        }
        
        SECTION("parser does not accept not matching input string")
        {
            using absinthe::parser_error;
            auto input_string = GENERATE(as<std::string>{}, "", "r", ".", "!", "\2");
            auto input = TestType(input_string.begin(), input_string.end());

            auto [it, parsed] = parse(input, parser);

            REQUIRE(it == input.begin());

            auto error = std::get_if<parser_error>(&parsed);
            REQUIRE(error != nullptr);
        }
    }
}

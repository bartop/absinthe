
#pragma once

#include "parse_result.hpp"

#include <string>
#include <variant>
#include <cctype>

namespace absinthe
{

namespace detail {

class function_char_parser {
public:
    using fun = int (*)(int);
    function_char_parser(const std::string& name, fun function) :
        m_name(name),  m_function(function) {}

    template<class It>
    constexpr parse_result<It, char> parse(It begin, It end) const
    {
        if (begin == end || !m_function(*begin))
            return { begin, parser_error{ m_name + " parser failed" } };

        auto result = *begin;

        return { ++begin, result };
    }

private:
    std::string m_name;
    fun m_function;
};

}

class alnum : public detail::function_char_parser
{
public:
    alnum() : function_char_parser{"alnum", &std::isalnum} {}
};

class alpha : public detail::function_char_parser
{
public:
    alpha() : function_char_parser{"alpha", &std::isalpha} {}
};

class blank : public detail::function_char_parser
{
public:
    blank() : function_char_parser{"blank", &std::isblank} {}
};

}

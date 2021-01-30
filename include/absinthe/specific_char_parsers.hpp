
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

class cntrl : public detail::function_char_parser
{
public:
    cntrl() : function_char_parser{"cntrl", &std::iscntrl} {}
};

class digit : public detail::function_char_parser
{
public:
    digit() : function_char_parser{"digit", &std::isdigit} {}
};

class graph : public detail::function_char_parser
{
public:
    graph() : function_char_parser{"graph", &std::isgraph} {}
};

class print : public detail::function_char_parser
{
public:
    print() : function_char_parser{"print", &std::isprint} {}
};

class punct : public detail::function_char_parser
{
public:
    punct() : function_char_parser{"punct", &std::ispunct} {}
};

class space : public detail::function_char_parser
{
public:
    space() : function_char_parser{"space", &std::isspace} {}
};

class xdigit : public detail::function_char_parser
{
public:
    xdigit() : function_char_parser{"xdigit", &std::isxdigit} {}
};

class lower : public detail::function_char_parser
{
public:
    lower() : function_char_parser{"lower", &std::islower} {}
};

class upper : public detail::function_char_parser
{
public:
    upper() : function_char_parser{"upper", &std::isupper} {}
};

}

#pragma once

#include <string>
#include <variant>

namespace absynth
{

class char_
{
public:
    char_(char parsed) : m_parsed_char(parsed)
    {
    }

    std::pair<std::string::const_iterator, std::variant<std::string, char>>
    parse(std::string::const_iterator begin, std::string::const_iterator end) const
    {
        if (begin == end || *begin != m_parsed_char)
            return { begin, "error" };

        return { ++begin, m_parsed_char };
    }

private:
    char m_parsed_char;
};

} // namespace absynth
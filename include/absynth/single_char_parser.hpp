#pragma once

#include <tuple>
#include <string>
#include <optional>

namespace absynth
{

class char_
{
public:
    char_(char parsed) : m_parsed_char(parsed)
    {
    }

    std::pair<std::string::const_iterator, std::optional<std::tuple<char>>>
    parse(std::string::const_iterator begin, std::string::const_iterator end) const
    {
        if (begin == end || *begin != m_parsed_char)
            return { begin, std::nullopt };

        return { ++begin, m_parsed_char };
    }

private:
    char m_parsed_char;
};

} // namespace absynth
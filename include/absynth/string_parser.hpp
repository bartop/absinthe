
#include <tuple>
#include <string>
#include <optional>
#include <utility>
#include <algorithm>

namespace absynth
{

class string_
{
public:
    string_(std::string parsed) : m_parsed_string(std::move(parsed))
    {
    }

    std::pair<std::string::const_iterator, std::tuple<std::optional<std::string>>>
    parse(std::string::const_iterator begin, std::string::const_iterator end) const
    {
        auto [parsed_it, input_it] = std::mismatch(
            m_parsed_string.begin(), m_parsed_string.end(),
            begin, end);

        if (parsed_it != m_parsed_string.end()) 
            return { begin, std::nullopt };
            
        return { input_it, m_parsed_string };
    }

private:
    std::string m_parsed_string;
};

} // namespace absynth
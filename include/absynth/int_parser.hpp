
#include <tuple>
#include <string>
#include <optional>
#include <utility>
#include <algorithm>

namespace absynth
{

class int_
{
public:
    std::pair<std::string::const_iterator, std::tuple<std::optional<int>>>
    parse(std::string::const_iterator begin, std::string::const_iterator end) const
    {
        if (begin == end)
            return {begin, std::nullopt};

        int sign = [&begin](){
            if (*begin != '-' && *begin != '+')
                return 1;

            return *begin++ == '+' ? 1 : -1;
        }();

        auto result = 0;
        auto it = begin;

        for (; it != end; ++it)
        {
            if (*it < '0' || *it > '9')
                break;

            result *= 10;
            result += *it - '0';
        }

        if (it == begin)
            return {begin, std::nullopt};

        return {it, sign * result};
    }
};

} // namespace absynth
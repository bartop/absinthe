
#include <string>

namespace absynth
{

template <class Parser>
auto parse(
    std::string::const_iterator it,
    std::string::const_iterator end,
    const Parser &parser) 
{
    return parser.parse(it, end);
}

} // namespace absynth
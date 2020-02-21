
#include <string>
#include <variant>
#include <tuple>
#include <type_traits>

namespace absynth
{


template<class Parser>
using parser_tuple_t = 
    typename decltype(
        std::declval<Parser>().parse(std::string::const_iterator{}, std::string::const_iterator{})
    )::second_type::value_type;


template<class Parser>
using parser_variant_t = 
    typename decltype(
        std::declval<Parser>().parse(std::string::const_iterator{}, std::string::const_iterator{})
    )::second_type;


template<class Parser>
using parser_result_t = std::decay_t<decltype(std::get<1>(std::declval<parser_variant_t<Parser>>()))>;


template<class T>
struct is_tuple
{
    constexpr static bool value = false;
};

template<class...Args>
struct is_tuple<std::tuple<Args...>>
{
    constexpr static bool value = true;


};

template<class T>
constexpr auto tuplize(T&& value)
{
    if constexpr (is_tuple<T>::value)
        return std::forward<T>(value);
    
    return std::tuple(value);
}


}





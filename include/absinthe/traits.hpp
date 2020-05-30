
#include <string>
#include <variant>
#include <tuple>
#include <type_traits>

namespace absinthe
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

template<class... Args>
struct is_tuple<std::tuple<Args...>>
{
    constexpr static bool value = true;
};

template<class T, class U>
struct variant_sum {
    using type = void;
};

template<class... Args1, class... Args2>
struct variant_sum<std::variant<Args1...>, std::variant<Args2...>> {
    using type = std::variant<Args1..., Args2...>;
};

template<class T, class U>
using variant_sum_t = typename variant_sum<T, U>::type;

template<class T>
struct is_variant : std::false_type {};

template<class... Args>
struct is_variant<std::variant<Args...>> : std::true_type {};

template<class T>
constexpr decltype(auto) variantize(T&& value) {
    if constexpr (is_variant<T>::value)
        return std::forward<T>(value);
    
    return std::variant<std::decay_t<T>>(std::forward<T>(value));
}

template<class T>
using variantized_t = decltype(variantize(std::declval<T>()));

template<class T>
constexpr decltype(auto) tuplize(T&& value)
{
    if constexpr (is_tuple<std::decay_t<T>>::value)
        return std::forward<T>(value);
    else
        return std::tuple(std::forward<T>(value));
}

}

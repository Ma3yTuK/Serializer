#ifndef STATIC_ITERATION_H
#define STATIC_ITERATION_H

#include <utility>

template<typename T, T... index, typename F>
constexpr void for_sequence(std::integer_sequence<T, index...>, const F& function)
{
    (function(std::integral_constant<T, index>{}), ...);
}

#endif // STATIC_ITERATION_H

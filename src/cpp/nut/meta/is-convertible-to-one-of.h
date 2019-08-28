#pragma once

#include <type_traits>

namespace Nut::Meta {

    /**
     * Returns `true` if `TFrom` is convertible to at least one type from `TTos`
     * set of types. 
     * 
     * If `sizeof...(TTos) == 0`, program is ill-formed.
     */
    template <typename TFrom, typename... TTos>
    constexpr inline bool IsConvertibleToOneOf = (std::is_convertible_v<TFrom, TTos> || ...);

}


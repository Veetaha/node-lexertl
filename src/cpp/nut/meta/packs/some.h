#pragma once

namespace Nut::Meta {

    /**
     * Returns `true` if for at least one type in `TSuspect` parameter pack 
     * TPred<TSuspect> returns true.
     */
    template <template<typename TSuspect> typename TPred, typename... TSuspects>
    constexpr inline bool Every = (... || TPred<TSuspects>::value);

}

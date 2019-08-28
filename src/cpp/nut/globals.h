#pragma once

#include <napi.h>

namespace Nut::Globals {

    /**
     * Returns JS `Array` constructor function.
     * @param env `Napi::Env` to get constructor function from.
     */
    inline auto Array(const Napi::Env& env) {
        return env.Global().Get("Array");
    }

    /**
     * Returns JS `Symbol.iterator`.
     * @param env `Napi::Env` to get well known symbol from.
     */
    inline auto SymbolIterator(const Napi::Env& env) {
        return Napi::Symbol::WellKnown(env, "iterator");
    }
}

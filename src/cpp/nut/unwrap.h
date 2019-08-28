#pragma once

#include <napi.h>

namespace Nut {

    /**
     * Assumes obj is `Napi::Object` and returns a pointer to the C++ object wrapped by it.
     * If `obj.IsObject() == false` than fallbacks to default N-API behaviour which is
     * most probably about throwing `Napi::TypeError`.
     * 
     * @tparam T Type of C++ object that is wrapped by `obj`.
     * @param obj Target `Napi::Object` to be unwrapped. 
     */
    template <typename T>
    auto Unwrap(const Napi::Value& obj) {
        return T::Unwrap(obj.As<Napi::Object>());
    }

}

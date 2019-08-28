#pragma once

#include <string>
#include <type_traits>
#include <napi.h>

#include "never.h"
#include "is-napi-wrapper-of.h"

namespace Nut::Meta {

    /**
     * Evaluates to `Napi::Number` or `Napi::Boolean` or `Napi::String`
     * according to the given C++ native type representative.
     * 
     * If `TValue` is `bool`, returns `Napi::Boolean`.
     * If `TValue` is some integral or floating point type, returns `Napi::Number`.
     * If `Tvalue` is 8 or 16 bit string or pointer to char, returns `Napi::String`.
     * 
     * Otherwise program is ill-formed, redundant compile errors are expected.
     */
    template <typename TValue>
    using NapiWrapperOf = 
        std::conditional_t<(IsNapiWrapperOf<TValue, Napi::Boolean>), Napi::Boolean,
        std::conditional_t<(IsNapiWrapperOf<TValue, Napi::Number >), Napi::Number,
        std::conditional_t<(IsNapiWrapperOf<TValue, Napi::String >), Napi::String,
            Never
        >>>;
}

#pragma once

#include <type_traits>
#include <napi.h>

#include "is-convertible-to-one-of.h"

namespace Nut::Meta {

    /**
     * Returns `true` if `TNapiWrapper` is `Napi::Boolean` or `Napi::Number` or
     * `Napi::String` and `TTarget` is one of C++ raw representations of it.
     * E.g. 
     * For Napi::Boolean, `TTarget` should be `bool`, 
     * For Napi::Number, `TTarget` should be `int64_t` or `double` or any other
     * arithmetic value.
     */
    template <typename TTarget, typename TNapiWrapper>
    constexpr inline bool IsNapiWrapperOf{false};

    template <typename TTarget>
    constexpr inline bool IsNapiWrapperOf<TTarget, Napi::Boolean> = (
        std::is_same_v<bool, TTarget>
    );

    
    template <typename TTarget> 
    constexpr inline bool IsNapiWrapperOf<TTarget, Napi::Number> = (
        std::is_arithmetic_v<TTarget> && !IsNapiWrapperOf<TTarget, Napi::Boolean>
    ); 

    // Why std::is_convertible but not std::is_same? See Napi::Value::From implementation.
    template <typename TTarget>
    constexpr inline bool IsNapiWrapperOf<TTarget, Napi::String> = (
        IsConvertibleToOneOf<TTarget, 
            const char *, 
            const char16_t *, 
            std::string, 
            std::u16string
        >
    );
}

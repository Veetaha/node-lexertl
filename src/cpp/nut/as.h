#pragma once

#include <type_traits>
#include <utility>
#include <string_view>
#include <napi.h>
#include <boost/mpl/contains.hpp>
#include <boost/type_traits/is_base_and_derived.hpp>

#include "numeric-cast.h"
#include "meta/is-napi-wrapper-of.h"
#include "meta/napi-wrapper-of.h"

namespace Nut {
    namespace Internal {
        template <bool Enable, typename TSuspect>
        using EnableIfIsNapiValue = std::enable_if_t<
            std::is_same_v<TSuspect, Napi::Value> == Enable, int
        >;

    }

    /**
     * Shortcut for `value.As<Napi::[WrapperType]>().[TTargetName]Value()`.
     * Doesn't setup new `Napi::HandleScope` for efficiency.
     * 
     * You get additional `valueName` parameter that is forwarded to
     * `NumericCast<>(value, valueName)` only for numeric `TTarget`, 
     * as a separate overload.
     * 
     * @tparam TTarget Target C++ type to convert `value` to. Currently only
     *         `bool`, numeric types and `std::[u16]string` are supported. 
     * @param value Napi::Value to convert to C++ counterpart.
     */
    template <typename TTarget, Internal::EnableIfIsNapiValue<false, TTarget> = 0>
    inline TTarget As(const Napi::Value& value) {
        static_assert(
            std::is_same_v<TTarget, std::remove_cvref_t<TTarget>>, 
            "Target type must not be cvref-qualified"
        );

        if constexpr (Meta::IsNapiWrapperOf<Napi::Number, TTarget>) {
            return NumericCast<TTarget>(value);
        } else if constexpr (boost::is_base_and_derived<Napi::Value, TTarget>::value) {
            return value.As<TTarget>();
        } else {
            return value.As<Meta::NapiWrapperOf<TTarget>>().operator TTarget();
        }
    }

    /**
     * Noop if `TTarget` is Napi::Value.
     */
    template <typename TTarget, Internal::EnableIfIsNapiValue<true, TTarget> = 0>
    inline const Napi::Value& As(const Napi::Value& value)  {
        return value;
    }

    // Separate overload for rvalue in order to have rvalue return type too.
    template <typename TTarget, Internal::EnableIfIsNapiValue<true, TTarget> = 0>
    inline Napi::Value&& As(Napi::Value&& value) {
        return std::move(value);
    }

    // Optimisation overload in order not to create intermediate Napi::Number inside
    // of NumericCast<> implementation
    template <typename TTarget>
    inline TTarget As(const Napi::Number& value) {
        return NumericCast<TTarget>(value);
    }
}

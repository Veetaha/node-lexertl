#pragma once

#include <type_traits>
#include <string_view>
#include <cmath>
#include <napi.h>
#include <boost/numeric/conversion/cast.hpp>
#include <fmt/core.h>

#include "meta/packs/every.h"

namespace Nut {

    /**
     *  Casts `TSource` to `TTarget` and throws `Napi::Error`
     *  if `TSource` value is out of range of `TTarget`.
     * 
     *  @tparam TSource Incomming type of number.
     *  @tparam TTarget Outcomming type of number.
     *  @param env `Napi::Env` to create `Napi::Error` in when cast is not successful.
     *  @param src Value to cast to `TTarget`.
     *
     */
    template<typename TTarget, typename TSource>
    constexpr TTarget NumericCast(
        const Napi::Env& env, 
        const TSource src
    ) {
        static_assert(Meta::Every<std::is_arithmetic, TTarget, TSource>);

        // Boost returns 0 when casting NaN to integral type
        if constexpr (std::is_integral_v<TTarget> && std::is_floating_point_v<TSource>) {
            if (std::isnan(src)) throw Napi::Error::New(
                env, "Failed to cast NaN to integer."
            );
        }
        try {
            return boost::numeric_cast<TTarget>(src);
        }
        catch (const boost::numeric::bad_numeric_cast&) {
            using TargetLimits = std::numeric_limits<TTarget>;
            throw Napi::Error::New(env, fmt::format(
                "Number {} is out of destination's type range, which is [{}, {}].", 
                src, TargetLimits::lowest(), TargetLimits::max()
            ));
        }
    }

    template<typename TTarget>
    inline constexpr TTarget NumericCast(const Napi::Number& src) {
        if constexpr (std::is_convertible_v<Napi::Number, TTarget>) {
            return src.operator TTarget();
        } else {
            return NumericCast<TTarget>(src.Env(), src.DoubleValue());
        }
    }

    template<typename TTarget>
    inline TTarget NumericCast(const Napi::Value& src) {
        return NumericCast<TTarget>(src.As<Napi::Number>());
    }
}

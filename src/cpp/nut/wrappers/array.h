#pragma once

#include <type_traits>
#include <utility>
#include <functional>
#include <napi.h>

#include "nut/as.h"

namespace Nut {

    class Array {
        Napi::Array m_arr;
    public: 
        explicit Array(const Napi::Value& arrObj): m_arr(arrObj.As<Napi::Array>()) {}
        explicit Array(Napi::Array && arrObj):     m_arr(std::move(arrObj)) {}

        auto Env() const {
            return m_arr.Env();
        }

        uint32_t Length() const {
            return m_arr.Length();
        }

        auto operator[](uint32_t index) const {
            return m_arr.Get(index);
        }

        /**
         * Performs `std::invoke(ivokeParams..., Nut::As<TItem>(item))` 
         * for each item in array.
         * Creates new `Napi::HandleScope` on each iteration.
         * 
         * Examples:
         * ```cpp
         * arr.ForEach([](Napi::Value&& item) { 
         *     // ...
         * })
         * arr.ForEach<int64_t>([] (int64_t item){
         *     // ...
         * });
         * arr.ForEach([](const Napi::Env& env, int someInt, Napi::Value&& item){
         *     // ...
         * }, env, 42);
         * arr.ForEach(&ThisClass::Method, this, 2, "", true);
         * // ThisClass::Method has the following signature:
         * // void Method(int a, char * str, bool flag, [const ]Napi::Value[&[&]] item);
         * ```
         * 
         */
        template <typename TItem = Napi::Value, typename... TInvokeParams>
        void ForEach(TInvokeParams&&... invokeParams) const {
            const auto env{Env()};
            
            const uint32_t length{ m_arr.Length() };
            for (uint32_t i{}; i < length; ++i) {
                Napi::HandleScope iterationScope{env};
                std::invoke(
                    std::forward<TInvokeParams>(invokeParams)...,
                    Nut::As<TItem>(m_arr.Get(i))
                );
            }
        }

    };

}

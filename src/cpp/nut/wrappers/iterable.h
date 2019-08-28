#pragma once

#include <utility>
#include <napi.h>

#include "nut/globals.h"
#include "nut/as.h"

#include "array.h"
#include "iterator.h"

namespace Nut {

    class Iterable {
        Napi::Object   m_iterable;
        Napi::Function m_createIteratorFn;

    public:
        explicit Iterable(Napi::Object&& iterableObj): 
            m_iterable(std::move(iterableObj)),
            m_createIteratorFn(m_iterable
                .Get(Globals::SymbolIterator(m_iterable.Env()))
                .As<Napi::Function>()
            )
        {}

        explicit Iterable(const Napi::Value& iterableObj): 
            Iterable(iterableObj.As<Napi::Object>())
        {}

        bool IsArray() const { return m_iterable.IsArray(); }
        auto Env()     const { return m_iterable.Env();     }

        auto CreateIterator() const {
            return Iterator{m_createIteratorFn.Call(m_iterable, 0, nullptr)};
        }

        /**
         * Pre: if `IsArray() === true`, than the following should be true
         * from the construction of the object and till this method call:
         * ```
         * m_iterable[Symbol.iterator] === Array.prototype[Symbol.iterator]
         * ```
         * This is used to optimize for a simple index-based iteration.
         * 
         * Performs `std::invoke(ivokeParams..., item)` for each item emitted by
         * `this` iterable. Defaults to getting JavaScript iterator and using it
         * to walk the sequence, but uses index-based iteration if `this->IsArray()`
         */
        template <
            typename    TItem,
            typename... TInvokeParams
        >
        void ForEach(TInvokeParams&&... invokeParams) const {
            // optimize for array since its iteration is much faster
            if (IsArray()) {
                return Array(m_iterable).ForEach<TItem>(std::forward<TInvokeParams>(invokeParams)...);
            }
            const auto env{Env()};
            Napi::HandleScope scope{env};

            auto iterator{CreateIterator()};
            auto iteratorResult{iterator.Next()};
            
            while (!iteratorResult.Done()) {
                Napi::HandleScope loopScope{env};
                std::invoke(
                    std::forward<TInvokeParams>(invokeParams)...,
                    Nut::As<TItem>(iteratorResult.Value())
                );
                iteratorResult = iterator.Next();
            }
        }
    };
}


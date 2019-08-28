#pragma once

#include <utility>
#include <napi.h>

#include "iterator-result.h"

namespace Nut {

    class Iterator {
        Napi::Object   m_iterator;
        Napi::Function m_iteratorNext;
    public:

        explicit Iterator(Napi::Object&& iteratorObj): 
            m_iterator(std::move(iteratorObj)),
            m_iteratorNext(m_iterator.Get("next").As<Napi::Function>())
        {}

        explicit Iterator(const Napi::Value& iteratorObj): 
            Iterator(iteratorObj.As<Napi::Object>())
        {}

        auto Next() {
            return IteratorResult { m_iteratorNext.Call(m_iterator, 0, nullptr) };
        }

    };

}

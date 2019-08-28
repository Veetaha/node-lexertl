#pragma once

#include <napi.h>

#include "nut/as.h"
#include "nut/macros/generate-getters.h"

namespace Nut {

    class IteratorResult {
        bool m_done;
        Napi::Value m_value;
    public:

        bool Done() const { return m_done; }    

        NUT_GENERATE_GETTERS(Value(), m_value)

        explicit IteratorResult(const Napi::Object& iteratorResultObj):
            m_done(Nut::As<bool>(iteratorResultObj.Get("done"))),
            m_value(m_done 
                ? iteratorResultObj.Get("value") 
                : iteratorResultObj.Env().Undefined() 
            )
        {}

        explicit IteratorResult(const Napi::Value& iteratorResultObj): 
            IteratorResult(iteratorResultObj.As<Napi::Object>()) 
        {}
    };

}

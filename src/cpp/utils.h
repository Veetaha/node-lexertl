#include <iostream>
#include <functional>
#include <napi.h>

namespace Utils {

    template <typename TMethodKey>
    auto CallMethod(
        Napi::Value instance, 
        const TMethodKey& methodKey, 
        const std::initializer_list<napi_value>& params
    ) {
        return instance
            .template As<Napi::Object>()
            .Get(methodKey)
            .template As<Napi::Function>()
            .Call(instance, params);
    }

    template <typename TValue>
    void ForEachInIterable(
        const Napi::Env& env,
        const Napi::Value& iterable, 
        const std::function<void(const TValue&)>& cb
    ) {
        const Napi::HandleScope scope{env};

        const auto symbolIterator { Napi::Symbol::WellKnown(env, "iterator") };

        const auto iterator { CallMethod(iterable, symbolIterator, {}).As<Napi::Object>() };

        const auto iteratorNext { iterator.Get("next").As<Napi::Function>() };

        do { 
            const Napi::HandleScope scope2{env};

            auto iterVal = iteratorNext.Call(iterator, {}).As<Napi::Object>();

            if (iterVal.Get("done").As<Napi::Boolean>().Value()) return;

            cb(iterVal.Get("value").As<TValue>());
        } while (true);
    }


}
#include <functional>
#include <napi.h>

namespace Utils {

    template <typename TValue>
    void ForEachInIterable(
        const Napi::Env& env,
        const Napi::Value& iterable, 
        const std::function<void(const TValue&)>& cb
    ) {
        const auto jsSymbolIterator { 
            env.Global().Get("Symbol").As<Napi::Object>().Get("iterator") 
        };

        const auto iterator { 
            iterable.As<Napi::Object>().Get(jsSymbolIterator).As<Napi::Object>() 
        };

        const auto iteratorNext {
            iterator.Get("next").As<Napi::Function>()
        };

        while (true) { 
            const Napi::HandleScope scope{env};

            const auto iterVal { 
                iteratorNext.Call(iterator, 0, nullptr).As<Napi::Object>() 
            };

            if (iterVal.Get("done").As<Napi::Boolean>().Value()) return;

            cb(iterVal.Get("value").As<TValue>());
        }
    }


}
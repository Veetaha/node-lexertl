#pragma once

#include <initializer_list>
#include <napi.h>

namespace Nut {

    /**
     * Calls method `methodKey` on the given object `self` with the given `params`.
     * 
     * @param self Object to set as JS `this` context for method call.
     * @param methodKey Key that is used as an argument of `self.Get(methodKey)` to
     *        retrieve method to be called from `self`.
     * @param params `std::inintializer_list` of parameters to pass to the ivoked method.
     */
    template <typename TMethodKey>
    auto CallMethod(
        const Napi::Object& self, 
        const TMethodKey& methodKey, 
        const std::initializer_list<napi_value>& params
    ) {
        return self
            .Get(methodKey)
            .template As<Napi::Function>()
            .Call(self, params);
    }

}


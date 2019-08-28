#pragma once

#include <napi.h>

#include "as.h"
#include "meta/napi-wrapper-of.h"

namespace Nut {

    /**
     * Returns `Nut::As<T>(info[index])` or copy of `defaultVal` if
     * index is out of bound of info parameter array.
     * 
     * @param info Target parameter array to get param from.
     * @param index Index of parameter to retrieve.
     * @param defaultVal Default parameter value to return of paramter array doesnt 
     *                   contain parameter under given index.
     * 
     */
    template <typename T>
    T GetDefaultParam(const Napi::CallbackInfo& info, size_t index, T defaultVal) {
        return index < info.Length() ? As<T>(info[index]) : defaultVal;
    }


}

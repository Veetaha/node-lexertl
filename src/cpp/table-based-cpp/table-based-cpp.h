#pragma once

#include <napi.h>

namespace TableBasedCpp {
    Napi::Value GenerateCpp(const Napi::CallbackInfo&);

    void Export(const Napi::Env& env, Napi::Object& exports);
}

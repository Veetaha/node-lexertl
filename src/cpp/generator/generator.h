#pragma once

#include <vector>
#include <napi.h>

namespace Generator {
    void Build(const Napi::CallbackInfo&);

    void Export(const Napi::Env& env, Napi::Object& exports);
};

#pragma once

#include <napi.h>

namespace TableBasedCpp {
    Napi::Value GenerateCpp(const Napi::CallbackInfo&);
}
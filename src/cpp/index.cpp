#include <napi.h>

#include "rules.h"

// TODO: export all modules

Napi::Object Init(Napi::Env env, Napi::Object exports) {
    exports.Set(Rules::name, Rules::GetClass(env));
    return exports;
}

NODE_API_MODULE(NODE_GYP_MODULE_NAME, Init)

#include <napi.h>

#include "generator.h"
#include "rules.h"
#include "state-machine.h"
#include "table-based-cpp.h"

// TODO: implement all lexertl modules

Napi::Object Init(Napi::Env env, Napi::Object exports) {

    Generator::Export(env, exports);
    Rules::Export(env, exports);
    StateMachine::Export(env, exports);
    TableBasedCpp::Export(env, exports);

    return exports;
}

NODE_API_MODULE(NODE_GYP_MODULE_NAME, Init)

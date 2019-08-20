#include <napi.h>

#include <lexertl/rules.hpp>
#include <lexertl/state_machine.hpp>
#include <lexertl/generator.hpp>
#include <lexertl/generate_cpp.hpp>

#include "generator.h"
#include "rules.h"
#include "state-machine.h"
#include "table-based-cpp.h"

// TODO: export all modules

Napi::Object Init(Napi::Env env, Napi::Object exports) {

    Generator::Export(env, exports);
    Rules::Export(env, exports);
    StateMachine::Export(env, exports);    
    TableBasedCpp::Export(env, exports);

    return exports;
}

NODE_API_MODULE(NODE_GYP_MODULE_NAME, Init)

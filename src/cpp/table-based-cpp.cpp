#include <sstream>
#include <napi.h>
#include <lexertl/generate_cpp.hpp>

#include "table-based-cpp.h"
#include "state-machine.h"

namespace TableBasedCpp {
    Napi::Value GenerateCpp(const Napi::CallbackInfo& info) {
        const auto  name { info[0].ToString().Utf8Value() };
        const auto& sm { StateMachine::Unwrap(info[1].ToObject())->GetStateMachine() };
        const auto  pointers { info[2].ToBoolean() };
        
        std::stringstream ss;

        lexertl::table_based_cpp::generate_cpp(name, sm, pointers, ss);
        
        return Napi::String::New(info.Env(), ss.str());
    }
}
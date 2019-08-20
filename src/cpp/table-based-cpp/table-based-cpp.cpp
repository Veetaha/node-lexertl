#include <sstream>
#include <napi.h>
#include <lexertl/generate_cpp.hpp>


#include "table-based-cpp.h"
#include "state-machine.h"

namespace TableBasedCpp {
    Napi::Value GenerateCpp(const Napi::CallbackInfo& info) {
        auto smObj { info[1].As<Napi::Object>() };
        auto smWrapper { StateMachine::Unwrap(smObj) };

        const auto  name { info[0].ToString().Utf8Value() };
        const auto& sm { smWrapper->GetStateMachine() };
        const auto  pointers { info[2].ToBoolean() };

        std::stringstream ss;
        
        lexertl::table_based_cpp::generate_cpp(name, sm, pointers.Value(), ss);
        
        return Napi::String::New(info.Env(), ss.str());
    }

    void Export(const Napi::Env& env, Napi::Object& exports) {
        auto ns { Napi::Object::New(env) };

        ns.Set("generateCpp", Napi::Function::New(env, &TableBasedCpp::GenerateCpp));
        
        exports.Set("TableBasedCpp", ns);
    }
}
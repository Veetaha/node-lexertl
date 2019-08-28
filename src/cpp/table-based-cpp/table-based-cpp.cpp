#include <sstream>
#include <napi.h>
#include <lexertl/generate_cpp.hpp>
#include <fmt/core.h>

#include "nut/macros/err-wrap.h"
#include "nut/unwrap.h"
#include "nut/as.h"
#include "nut/get-default-param.h"

#include "table-based-cpp.h"
#include "state-machine.h"

namespace TableBasedCpp {
    Napi::Value GenerateCpp(const Napi::CallbackInfo& info) {
        const auto env{info.Env()};

        const auto  name { Nut::As<std::string>(info[0]) };
        const auto& sm { Nut::Unwrap<StateMachine>(info[1])->GetStateMachine() };
        const auto  pointers { Nut::GetDefaultParam(info, 2, false) };
        
        std::stringstream ss; 
        
        NUT_ERR_WRAP(env, {

            lexertl::table_based_cpp::generate_cpp(name, sm, pointers, ss);

        });
        
        return Napi::String::New(env, ss.str());
    }

    void Export(const Napi::Env& env, Napi::Object& exports) {
        auto ns { Napi::Object::New(env) };

        ns.Set("generateCpp", Napi::Function::New(env, &TableBasedCpp::GenerateCpp));
        
        exports.Set("TableBasedCpp", ns);
    }
}

#include <napi.h>
#include <vector>

#include <lexertl/generator.hpp>
#include <lexertl/generate_cpp.hpp>

#include "nut/unwrap.h"

#include "rules.h"
#include "state-machine.h"

namespace Generator {
    void Build(const Napi::CallbackInfo& info) {

        const auto& rules { Nut::Unwrap<Rules>(info[0])->GetRules() };
        auto& sm { Nut::Unwrap<StateMachine>(info[1])->GetStateMachine() };

        try {
            lexertl::generator::build(rules, sm);
        } catch (const lexertl::runtime_error& err) {
            throw Napi::Error::New(info.Env(), err.what());
        }
    }


    void Export(const Napi::Env& env, Napi::Object& exports) {
        auto ns { Napi::Object::New(env) };
        
        ns.Set("build", Napi::Function::New(env, &Generator::Build));

        exports.Set("Generator", ns);
    }
}

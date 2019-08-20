#include <napi.h>
#include <vector>

#include <lexertl/generator.hpp>
#include <lexertl/generate_cpp.hpp>

#include "rules.h"
#include "state-machine.h"

namespace Generator {
    void Build(const Napi::CallbackInfo& info) {

        const auto& rules { Rules::Unwrap(info[0].As<Napi::Object>())->GetRules() };
        auto& sm {   StateMachine::Unwrap(info[1].As<Napi::Object>())->GetStateMachine() };

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
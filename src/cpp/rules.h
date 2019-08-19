#pragma once

#include <napi.h>

#include <lexertl/rules.hpp>

class Rules : public Napi::ObjectWrap<Rules> {
public:
    using Super = Napi::ObjectWrap<Rules>;
    using Super::Super;

    static constexpr const char * const name = "Rules";
    
    Rules(const Napi::CallbackInfo&);

    auto& GetRules() & { return m_rules; }
    void Push(const Napi::CallbackInfo&);


    static auto GetClass(const Napi::Env& env) {
        return DefineClass(env, name, {
            InstanceMethod("push", &Push)
        });
    }

private:
    using IdType = lexertl::rules::id_type;
    lexertl::rules m_rules;    

    static void EnsureValidLexemeIdOrFail(const Napi::Env& env, uint32_t id);
};
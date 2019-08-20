#pragma once

#include <napi.h>

#include <lexertl/rules.hpp>

class Rules : public Napi::ObjectWrap<Rules> {
public:
    using Super = Napi::ObjectWrap<Rules>;
    using Super::Super;

    static constexpr const char * const name { "Rules" };
    
    Rules(const Napi::CallbackInfo&);

    const auto& GetRules() const& { return m_rules; }
    lexertl::rules& GetRules() && = delete;
    
    void Push(const Napi::CallbackInfo&);
    void PushImpl(const Napi::Env& env, const Napi::Object& rule);

    static void Export(const Napi::Env& env, Napi::Object& exports);

private:
    using IdType = lexertl::rules::id_type;
    lexertl::rules m_rules;    

    static void EnsureValidLexemeIdOrFail(const Napi::Env& env, uint32_t id);
};
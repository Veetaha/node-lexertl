#pragma once

#include <napi.h>

#include <lexertl/rules.hpp>

#include "nut/macros/generate-getters.h"

class Rules : public Napi::ObjectWrap<Rules> {
    using IdType = lexertl::rules::id_type;

    lexertl::rules m_Rules;
    int i{};
public:
    using Super = Napi::ObjectWrap<Rules>;

    static constexpr const auto s_Name{ "Rules" };

    static void Export(const Napi::Env& env, Napi::Object& exports);
    
    Rules(const Napi::CallbackInfo&);

    NUT_GENERATE_GETTERS(GetRules(), m_Rules)
    
    void Push(const Napi::CallbackInfo&);
    void PushImpl(const Napi::Env& env, const Napi::Object& rule);

};


#pragma once

#include <napi.h>

#include <lexertl/state_machine.hpp>

#include "nut/macros/generate-getters.h"

class StateMachine : public Napi::ObjectWrap<StateMachine> {
    lexertl::state_machine m_StateMachine;
public:
    using Super = Napi::ObjectWrap<StateMachine>;
    using Super::Super;

    static constexpr const auto s_Name{ "StateMachine" };

    static void Export(const Napi::Env& env, Napi::Object& exports);

    NUT_GENERATE_GETTERS(GetStateMachine(), m_StateMachine)

    void Minimize(const Napi::CallbackInfo&);

};

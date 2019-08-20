#pragma once

#include <napi.h>

#include <lexertl/state_machine.hpp>

class StateMachine : public Napi::ObjectWrap<StateMachine> {
public:
    using Super = Napi::ObjectWrap<StateMachine>;
    using Super::Super;

    static constexpr const char * const name { "StateMachine" };
    
    auto& GetStateMachine() & { return m_stateMachine; }

    void Minimize(const Napi::CallbackInfo&);

    static void Export(const Napi::Env& env, Napi::Object& exports);

private:
    lexertl::state_machine m_stateMachine;  
};
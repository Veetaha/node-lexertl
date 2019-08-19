#pragma once

#include <napi.h>

#include <lexertl/state_machine.hpp>

class StateMachine : public Napi::ObjectWrap<StateMachine> {
public:
    using Super = Napi::ObjectWrap<StateMachine>;
    using Super::Super;
    
    auto& GetStateMachine() & { return m_stateMachine; }
    void Minimize(const Napi::CallbackInfo&) {
        m_stateMachine.minimise();
    }

private:
    lexertl::state_machine m_stateMachine;    
};
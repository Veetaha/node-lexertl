#include <napi.h>

#include "state-machine.h"

void StateMachine::Minimize(const Napi::CallbackInfo&) {
    m_stateMachine.minimise();
}

void StateMachine::Export(const Napi::Env& env, Napi::Object& exports) {
    exports.Set(name, DefineClass(env, name, {
        InstanceMethod("minimize", &StateMachine::Minimize)
    }));
}
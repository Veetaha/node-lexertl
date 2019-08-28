#include <napi.h>

#include "state-machine.h"

void StateMachine::Minimize(const Napi::CallbackInfo&) {
    m_StateMachine.minimise();
}

void StateMachine::Export(const Napi::Env& env, Napi::Object& exports) {
    exports.Set(s_Name, DefineClass(env, s_Name, {
        InstanceMethod("minimize", &StateMachine::Minimize)
    }));
}

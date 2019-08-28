#include <limits>
#include <napi.h>
#include <fmt/format.h>
#include <lexertl/rules.hpp>

#include "nut/numeric-cast.h"
#include "nut/macros/err-wrap.h"
#include "nut/wrappers/iterable.h"

#include "nut/macros/constructor-err-workaround-wrap.h"

#include "rules.h"

Rules::Rules(const Napi::CallbackInfo& info): Super(info) {
    if (!info[0].IsObject()) {
        return;
    }
    NUT_CONSTRUCTOR_ERR_WORKAROUND_WRAP("Rules", {
        const auto env{info.Env()};
        Nut::Iterable{info[0]}.ForEach<Napi::Object>(&Rules::PushImpl, this, env);
    });
}

void Rules::PushImpl(const Napi::Env& env, const Napi::Object& rule) {
    NUT_ERR_WRAP(env, {
        m_Rules.push(
            Nut::As<std::string>(rule.Get("regex")),
            Nut::NumericCast<IdType>(rule.Get("id"))
        );
    });

}


void Rules::Push(const Napi::CallbackInfo& info) {
    const auto env{info.Env()};
    PushImpl(env, info[0].As<Napi::Object>());
}

void Rules::Export(const Napi::Env& env, Napi::Object& exports) {
    exports.Set(s_Name, DefineClass(env, s_Name, {
        InstanceMethod("push", &Rules::Push)
    }));
}

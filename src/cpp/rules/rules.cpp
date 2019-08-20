#include <sstream>
#include <limits>
#include <napi.h>

#include <lexertl/rules.hpp>

#include "rules.h"
#include "utils.h"

Rules::Rules(const Napi::CallbackInfo& info): Super(info) {
    if (!info[0].IsObject()) return;
    const auto env{info.Env()};

    Utils::ForEachInIterable<Napi::Object>(env, info[0], [this, &env](const Napi::Object& rule){
        PushImpl(env, rule);
    });
}

void Rules::PushImpl(const Napi::Env& env, const Napi::Object& rule) {
    const Napi::HandleScope scope(env);

    const uint32_t id { rule.Get("id").As<Napi::Number>().Uint32Value() };

    EnsureValidLexemeIdOrFail(env, id);

    m_rules.push(
        rule.Get("regex").As<Napi::String>().Utf8Value(),
        static_cast<IdType>(id)
        // TODO add more params
    );
}

void Rules::Push(const Napi::CallbackInfo& info) {
    PushImpl(info.Env(), info[0].As<Napi::Object>());
}

void Rules::EnsureValidLexemeIdOrFail(const Napi::Env& env, uint32_t id) {
    constexpr const auto maxId { std::numeric_limits<IdType>::max() };

    if (id <= maxId) return;

    std::stringstream ss { "Lexeme id is too big, expected value in range [0, " };

    ss << maxId << "], but got " << id;

    throw Napi::Error::New(env, ss.str());
}

void Rules::Export(const Napi::Env& env, Napi::Object& exports) {
    exports.Set(name, DefineClass(env, name, {
        InstanceMethod("push", &Rules::Push)
    }));
}
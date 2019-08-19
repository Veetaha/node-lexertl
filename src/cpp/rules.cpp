#include <napi.h>

#include <lexertl/rules.hpp>

#include "rules.h"
#include "utils.h"

Rules::Rules(const Napi::CallbackInfo& info): Super(info) {
    if (!info[0].IsObject()) return;
    const auto env{info.Env()};

    Utils::ForEachInIterable<Napi::Object>(env, info[0], [this, &env](const Napi::Object& rule){
        const Napi::HandleScope scope(env);

        const uint32_t id { rule.Get("id").As<Napi::Number>().Uint32Value() };
        EnsureValidLexemeIdOrFail(env, id);

        m_rules.push(
            rule.Get("regex").As<Napi::String>().Utf8Value(),
            static_cast<IdType>(id)
            // TODO add more params
        );
    });

}


void Rules::EnsureValidLexemeIdOrFail(const Napi::Env& env, uint32_t id) {
    constexpr const auto maxId { std::numeric_limits<IdType>::max() };

    if (id <= maxId) return;

    std::string msg{ "Lexeme id is too big, expected value in range [0, " };
    msg += maxId;
    msg += "], but got ";
    msg += id;
    throw Napi::Error::New(env, msg);
}
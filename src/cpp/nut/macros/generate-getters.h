#pragma once

#include <type_traits>

#define NUT_GENERATE_GETTERS(SIGNATURE, GET_EXPR)                            \
    [[nodiscard]] auto&       SIGNATURE &      noexcept { return GET_EXPR; } \
    [[nodiscard]] const auto& SIGNATURE const& noexcept { return GET_EXPR; } \
    [[nodiscard]] auto        SIGNATURE &&                                   \
    noexcept(noexcept(decltype(GET_EXPR)(GET_EXPR)))   {                     \
        return GET_EXPR;                                                     \
    }                                                                        \
    int SIGNATURE const && = delete;


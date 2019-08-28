#pragma once

#include <exception>
#include <napi.h>

/** Rethrows std::exception thrown by the passed code block as Napi::Error. */
#define NUT_ERR_WRAP(ENV, ...)               \
try {                                        \
    __VA_ARGS__                              \
} catch (const std::exception& err) {        \
    throw Napi::Error::New(ENV, err.what()); \
}

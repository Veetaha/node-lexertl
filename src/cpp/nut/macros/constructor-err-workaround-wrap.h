#pragma once

#include <iostream>

#define NUT_CONSTRUCTOR_ERR_WORKAROUND_WRAP(CLASS_NAME, ...)                                 \
try {                                                                                        \
    __VA_ARGS__                                                                              \
} catch (const std::exception& err) {                                                        \
    std::cerr << "AHTUNG! Failed at construction of "#CLASS_NAME ": "<< err.what() <<        \
        "\nCurrent version of N-API crashes when throwing from C++ constructor\n"            \
        "so no JavaScript error was thrown. However this means that the created object\n"    \
        "is in an invalid state. Any interaction with it has undefined behaviour.\n"         \
        "Please, inspect the place where this constructor was called and try to\n"           \
        "provide its successful execution otherwise feel free to create an issue.\n"         \
        "You can follow this bug here https://github.com/nodejs/node-addon-api/pull/475.\n"; \
}

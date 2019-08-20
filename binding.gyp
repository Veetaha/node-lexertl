{
  "targets": [{
        # myModule is the name of your native addon
        'target_name': 'lexertl',

        'sources': [
            'src/cpp/index.cpp',
            'src/cpp/generator/generator.cpp',
            'src/cpp/rules/rules.cpp',
            'src/cpp/state-machine/state-machine.cpp',
            'src/cpp/table-based-cpp/table-based-cpp.cpp',
        ],
        # from Napi docs:
        'include_dirs': [
            "<!@(node -p \"require('node-addon-api').include\")",
            "vendor/lexertl14/include",
            "src/cpp",
            "src/cpp/generator",
            "src/cpp/rules",
            "src/cpp/state-machine",
            "src/cpp/table-based-cpp"
        ],
        'dependencies': ["<!(node -p \"require('node-addon-api').gyp\")"],

        # enable exceptions
        'cflags!': ['-fno-exceptions'],
        'cflags_cc!': ['-fno-exceptions'],

        'xcode_settings': {
            'GCC_ENABLE_CPP_EXCEPTIONS': 'YES',
            'CLANG_CXX_LIBRARY': 'libc++',
            'MACOSX_DEPLOYMENT_TARGET': '10.7',
        },

        'msvs_settings': {
            'VCCLCompilerTool': {'ExceptionHandling': 1},
        },
        'conditions': [
            ['OS=="mac"', {
                'cflags+': ['-fvisibility=hidden'],
                'xcode_settings': {
                    'GCC_SYMBOLS_PRIVATE_EXTERN': 'YES',  # -fvisibility=hidden
                }
            }]
        ]
    }]
}
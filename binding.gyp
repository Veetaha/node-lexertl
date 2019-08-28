{
    "targets": [{
        # 'configurations': {
        #     'Debug': {
        #         'cflags_cc': []
        #     }
        # },
        'target_name': '<(module_name)',
        'product_dir': '<(module_path)',

        'defines': [
            'NAPI_VERSION=<(napi_build_version)'
        ],

        'libraries': [
            '../conan/modules/lib/libfmt.a'
        ],

        'sources': [
            'src/cpp/index.cpp',
            'src/cpp/generator/generator.cpp',
            'src/cpp/rules/rules.cpp',
            'src/cpp/state-machine/state-machine.cpp',
            'src/cpp/table-based-cpp/table-based-cpp.cpp'
        ],
        'include_dirs': [
            '<!@(node -p "require(\'node-addon-api\').include")',

            # dependencies
            'conan/modules/include',
            'vendor/lexertl14/include',

            # sources
            'src/cpp',
            'src/cpp/generator',
            'src/cpp/rules',
            'src/cpp/state-machine',
            'src/cpp/table-based-cpp'
        ],

        'dependencies': ["<!(node -p \"require('node-addon-api').gyp\")"],

        # Taken from Napi docs:
        # TODO: investigate what all those settings do
        # enable exceptions
        'cflags!':    ['-fno-exceptions'],
        'cflags_cc!': ['-fno-exceptions'],
        'cflags_cc':  ['-std=gnu++2a'],

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

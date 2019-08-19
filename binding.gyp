{
  "targets": [{
        # myModule is the name of your native addon
        'target_name': 'lexert',

        'sources': [
            'src/cpp/index.cpp',
            'src/cpp/lexertl.cpp'
        ],
        # from Napi docs:
        'include_dirs': [
            "<!@(node -p \"require('node-addon-api').include\")",
            "vendor/lexertl14/include"
        ],
        'dependencies': ["<!(node -p \"require('node-addon-api').gyp\")"],

        # enable exceptions
        'cflags!': [ '-fno-exceptions' ],
        'cflags_cc!': [ '-fno-exceptions' ],

        'xcode_settings': {
            'GCC_ENABLE_CPP_EXCEPTIONS': 'YES',
            'CLANG_CXX_LIBRARY': 'libc++',
            'MACOSX_DEPLOYMENT_TARGET': '10.7',
        },

        'msvs_settings': {
            'VCCLCompilerTool': { 'ExceptionHandling': 1 },
        },
        'conditions': [
            ['OS=="mac"', {
                'cflags+': ['-fvisibility=hidden'],
                'xcode_settings': {
                    'GCC_SYMBOLS_PRIVATE_EXTERN': 'YES', # -fvisibility=hidden
                }
            }]
        ]
    }]
}
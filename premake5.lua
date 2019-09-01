workspace "lexertl" 
    configurations { "Debug", "Release" }
    architecture "x64"
    startproject "lexertl"

project "lexertl"
    language   "C++"
    buildoptions { 
        "-std=gnu++2a" -- cppdialect doesn't support gnu++2a
    }
    
    -- Though we specify dynamic library traget, it will be linked statically, see:
    -- https://emscripten.org/docs/compiling/Building-Projects.html#dynamic-linking
    -- https://emscripten.org/docs/compiling/Building-Projects.html#archive-a-files
    kind    "ConsoleApp" 

    targetname "%{prj.name}.js"
    location   "build/wasm"
    targetdir  "build/wasm/bin"
    objdir     "build/wasm/bin-int"

    files { "src/**.cpp"}--, "vendor/fmt/build/libfmt.a" }
    includedirs { 
        "src",
        "conan/modules/include",
        "vendor/*/include"
    }
    libdirs { "conan/modules/lib", "vendor/fmt/build" }
    links { "fmt" }

    filter "configurations:Debug"
        runtime "Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        runtime  "Release"
        defines  { "NDEBUG" }
        optimize "Speed"

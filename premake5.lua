workspace "lexertl" 
    configurations { "Debug", "Release" }
    architecture "x64"
    startproject "lexertl"

project "lexertl"
    language   "C++"
    buildoptions { 
        "-std=gnu++2a" -- workaround because `cppdialect "gnu++2a"` is not allowed
    }
    kind    "ConsoleApp" 

    targetname "lexertl.js"
    location   "build/wasm"
    targetdir  "build/wasm/bin"
    objdir     "build/wasm/bin-int"

    files { "src/**.cpp" }
    includedirs { 
        "src",
        "conan/modules/include",
        "vendor/*/include"
    }
    libdirs { 
        "conan/modules/lib", 
        "vendor/fmt/build" 
    }
    links { "fmt" }

    filter "configurations:Debug"
        runtime "Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        runtime  "Release"
        defines  { "NDEBUG" }
        optimize "Speed"

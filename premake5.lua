workspace "Zyn"
    configurations { "Debug", "Release" }

project "Zyn"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"

    pchheader "src/zynpch.h"

    includedirs {
        "src"
    }

    files { "src/**.h", "src/**.cpp" }

    filter { "configurations:Debug" }
        defines { "DEBUG" }
        symbols "On"

    filter { "configurations:Release" }
        defines { "NDEBUG" }
        optimize "On"

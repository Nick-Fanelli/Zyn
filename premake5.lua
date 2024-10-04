workspace "ProgrammingLanguage"
    configurations { "Debug", "Release" }

project "ProgrammingLanguage"
    kind "ConsoleApp"
    language "C++"
    files { "src/**.h", "src/**.cpp" }

    filter { "configurations:Debug" }
        defines { "DEBUG" }
        symbols "On"

    filter { "configurations:Release" }
        defines { "NDEBUG" }
        optimize "On"
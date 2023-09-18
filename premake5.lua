workspace "Nox"
    architecture "x64"

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Establecer Sandbox como el proyecto de inicio
startproject "Sandbox"

project "Nox"
    location "Nox"
    kind "SharedLib"
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "%{prj.name}/src",
        "%{prj.name}/vendor/spdlog/include"
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"

        defines
        {
            "NOX_PLATFORM_WINDOWS",
            "NOX_BUILD_DLL"
        }

        postbuildcommands
        {
            ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
        }

    filter "configurations:Debug"
        defines "NOX_DEBUG"
        symbols "On"

    filter "configurations:Release"
        defines "NOX_RELEASE"
        optimize "On"

    filter "configurations:Dist"
        defines "NOX_DIST"
        optimize "On"

project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "Nox/vendor/spdlog/include",
        "Nox/src"
    }

    links
    {
        "Nox"
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"

        defines
        {
            "NOX_PLATFORM_WINDOWS"
        }

    filter "configurations:Debug"
        defines "NOX_DEBUG"
        symbols "On"

    filter "configurations:Release"
        defines "NOX_RELEASE"
        optimize "On"

    filter "configurations:Dist"
        defines "NOX_DIST"
        optimize "On"

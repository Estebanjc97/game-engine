workspace "Nox"
    architecture "x64"

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Inlcuire las rutas relativas a cada carpeta en un directorio
IncludeDir = {}
IncludeDir["GLFW"] = "Nox/vendor/GLFW/include"

-- Establecer Sandbox como el proyecto de inicio
startproject "Sandbox"

include "Nox/vendor/GLFW"

project "Nox"
    location "Nox"
    kind "SharedLib"
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "Noxpch.h"
    pchsource "Nox/src/Noxpch.cpp"

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "%{prj.name}/src",
        "%{prj.name}/vendor/spdlog/include",
        "%{IncludeDir.GLFW}"
    }

    links
    {
        "GLFW",
        "opengl32.lib"
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
            "{MKDIR} ../bin/" .. outputdir .. "/Sandbox", -- Crea la carpeta si no existe
            ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox") -- Copia y pega el archivo Nox.dll (El engine) dentro de la Carpeta Sandbox
        }

    filter "configurations:Debug"
        defines "NOX_DEBUG"
        buildoptions "/MDd"
        symbols "On"

    filter "configurations:Release"
        defines "NOX_RELEASE"
        buildoptions "/MD"
        optimize "On"

    filter "configurations:Dist"
        defines "NOX_DIST"
        buildoptions "/MD"
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
        buildoptions "/MDd"
        symbols "On"

    filter "configurations:Release"
        defines "NOX_RELEASE"
        buildoptions "/MD"
        optimize "On"

    filter "configurations:Dist"
        defines "NOX_DIST"
        buildoptions "/MD"
        optimize "On"

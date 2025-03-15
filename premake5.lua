workspace "BMRecord_Demo"

    architecture "x64"

    configurations
    {
        "Debug",
        "Release"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Demo"
    kind "ConsoleApp"
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("obj/" .. outputdir .. "/%{prj.name}")

    files
    {
        "src/**.h",
        "src/**.cpp",
    }

    includedirs
    {
        "lib/spdlog/include",
        "lib/BMRecord/include"
    }

    links
    {
        "BMRecord_Lib"
    }

    libdirs 
    {
        "lib/BMRecord"
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"
        buildoptions "/utf-8"

        defines
        {
            "_BMR_PLATFORM_WINDOWS_",
            "_BMR_DYNAMIC_LINK_"
        }

        prebuildcommands
        {
            ("{COPYFILE} lib/BMRecord/ConfigBMRecord.bit ./"),
        }

        postbuildcommands
        {
            ("{COPYFILE} lib/BMRecord/ConfigBMRecord.bit bin/" .. outputdir .. "/%{prj.name}"),
            ("{COPYFILE} lib/BMRecord/BMRecord_Lib.dll bin/" .. outputdir .. "/%{prj.name}"),
            ("{COPYFILE} lib/OpalKelly/okFrontPanel.dll bin/" .. outputdir .. "/%{prj.name}"),
        }

    filter "configurations:Debug"
        defines "BMR_DEBUG"
        symbols "On"

    filter "configurations:Release"
        defines "BMR_RELEASE"
        optimize "On"
    
    filter {"system:windows", "configurations:Release"}
        buildoptions "/MT"
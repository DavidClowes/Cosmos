workspace "Cozmos"
	architecture "x64"
	startproject "Sandbox"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Cozmos"
	location "Cozmos"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "cozpch.h"
	pchsource "Cozmos/Source/cozpch.cpp"

	files
	{
		"%{prj.name}/Source/**.h",
		"%{prj.name}/Source/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/Source",
		"%{prj.name}/vendor/spdlog/include"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"COZ_PLATFORM_WINDOWS",
			"COZ_BUILD_DLL"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Sandbox/\"")
		}

	filter "configurations:Debug"
		defines "COZ_Debug"
		symbols "On"

	filter "configurations:Release"
		defines "COZ_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "COZ_DIST"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/Source/**.h",
		"%{prj.name}/Source/**.cpp"
	}

	includedirs
	{
		"Cozmos/vendor/spdlog/include",
		"Cozmos/Source"
	}

	links
	{
		"Cozmos"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"COZ_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "COZ_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "COZ_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "COZ_DIST"
		optimize "On"
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

-- Include directories relative to root folder (solution dir)
IncludeDir = {}
IncludeDir["GLFW"] = "Cozmos/vendor/GLFW/include"
IncludeDir["Glad"] = "Cozmos/vendor/Glad/include"
IncludeDir["ImGui"] = "Cozmos/vendor/imgui"
IncludeDir["glm"] = "Cozmos/vendor/glm"

group "Dependencies"
	include "Cozmos/vendor/GLFW"
	include "Cozmos/vendor/Glad"
	include "Cozmos/vendor/imgui"
group ""

project "Cozmos"
	location "Cozmos"
	kind "SharedLib"
	language "C++"
	staticruntime "off"

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
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}"
	}

	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines
		{
			"COZ_PLATFORM_WINDOWS",
			"COZ_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Sandbox/\"")
		}

	filter "configurations:Debug"
		defines "COZ_Debug"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "COZ_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "COZ_DIST"
		runtime "Release"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	staticruntime "off"

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
		"Cozmos/Source",
		"Cozmos/vendor",
		"%{IncludeDir.glm}"
	}

	links
	{
		"Cozmos"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines
		{
			"COZ_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "COZ_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "COZ_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "COZ_DIST"
		runtime "Release"
		optimize "On"
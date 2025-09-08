workspace "Atmos"
	architecture "x64"
	startproject "Atmos"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

	flags
	{
		"MultiProcessorCompile"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "Atmos/vendor/GLFW/include"
IncludeDir["Glad"] = "Atmos/vendor/Glad/include"
IncludeDir["imgui"] = "Atmos/vendor/imgui"
IncludeDir["glm"] = "Atmos/vendor/glm"
IncludeDir["stb_image"] = "Atmos/vendor/stb_image"
IncludeDir["entt"] = "Atmos/vendor/entt/include"

group "Dependencies"
	include "Atmos/vendor/GLFW"
	include "Atmos/vendor/Glad"
	include "Atmos/vendor/imgui"

group ""

project "Atmos"
	location "Atmos" 
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "pch.h"
	pchsource "Atmos/src/pch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/stb_image/**.h",
		"%{prj.name}/vendor/stb_image/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl"
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS",
		"GLFW_INCLUDE_NONE"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.imgui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}",
		"%{IncludeDir.entt}"
	}

	links
	{
		"GLFW",
		"Glad",
		"imgui",
		"opengl32.lib"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
		}

	filter "configurations:Debug"
		defines "SL_DEBUG"
		symbols "on"
		buildoptions "/utf-8"
		runtime "Debug"

	filter "configurations:Release"
		defines "SL_RELEASE"
		optimize "on"
		buildoptions "/utf-8"
		runtime "Release"

	filter "configurations:Dist"
		defines "SL_DIST"
		optimize "on"
		buildoptions "/utf-8"
		runtime "Release"
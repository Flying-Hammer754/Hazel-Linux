-- include "./vendor/premake/premake_customization/solution_items.lua"
include "Dependencies.lua"

workspace "Hazel"
	architecture "x86_64"
	startproject "Hazelnut"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

	--[[ solution_items
	{
		".editorconfig"
	} ]]

	flags
	{
		"MultiProcessorCompile"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

newoption {
	trigger = "disable-audio",
	description = "Disables Hazel's Audio System, results in faster compilation and smaller executable, Only disable if it is unused."
}

newoption {
	trigger = "disable-file-dialogs",
	description = "Disables Hazel's File Dialog(Open/Save) Functionality, results in faster compilation and smaller excutable, Only disable if it is unused."
}

group "Dependencies"
	--include "vendor/premake"
	include "Hazel/vendor/Box2D"
	include "Hazel/vendor/GLFW"
	include "Hazel/vendor/Glad"
	--include "Hazel/vendor/glad_gl3-3"
	--include "Hazel/vendor/glad_gl3-3_debug"
	include "Hazel/vendor/imgui"
	include "Hazel/vendor/yaml-cpp"
	filter { "not options:disable-file-dialogs" }
	include "Hazel/vendor"
	filter { "not options:disable-audio" }
	include "Hazel/vendor/openal-soft"
	filter {}
group ""

include "Hazel"
include "Sandbox"
filter { "not options:disable-file-dialogs" }
include "Hazelnut"
filter {}
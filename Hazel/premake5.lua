project "Hazel"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "off"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "hzpch.h"
	pchsource "src/hzpch.cpp"

	files
	{
		"src/**.h",
		"src/**.cpp",
		"vendor/stb_image/**.h",
		"vendor/stb_image/**.cpp",
		"vendor/glm/glm/**.hpp",
		"vendor/glm/glm/**.inl",
		"%{IncludeDir.nfd}/*",

		"vendor/ImGuizmo/ImGuizmo.h",
		"vendor/ImGuizmo/ImGuizmo.cpp"
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS",
		"GLFW_INCLUDE_NONE"
	}

	includedirs
	{
		"src",
		"vendor/spdlog/include",
		"%{IncludeDir.Box2D}",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}",
		"%{IncludeDir.entt}",
		"%{IncludeDir.yaml_cpp}",
		"%{IncludeDir.ImGuizmo}",
		"%{IncludeDir.VulkanSDK}",
		"%{IncludeDir.nfd}",
		"%{IncludeDir.SPIRV_Cross}",
		"%{IncludeDir.shaderc}",
		"%{IncludeDir.openal_soft}"
	}

	links
	{
		"Box2D",
		"GLFW",
		"Glad",
		"ImGui",
		"yaml-cpp",
		"nfd",
		"opengl32.lib",
		"openal-soft"
	}

	filter "files:vendor/ImGuizmo/**.cpp"
	flags { "NoPCH" }

	filter "system:windows"
		systemversion "latest"

		defines
		{
		}
	filter "system:linux"
		--files { "vendor/nativefiledialog-extended/src/nfd_portal.cpp" }
		links { "sndfile", "GL", "X11", "dbus-1", "%{Library.ShaderC_Debug}", "%{Library.SPIRV_Cross_Debug}", "%{Library.SPIRV_Cross_GLSL_Debug}", "%{Library.SPIRV_Tools_Debug}", "%{Library.SPIRV_Tools_opt}", "%{Library.glslang}", "%{Library.glslang_code_gen}", "%{Library.glslang_machine_independent}", "%{Library.SPIRV_Cross_Util}", "%{Library.glslang_spirv}", "%{Library.glslang_default_resource_limits}", "%{Library.glslang_os_dependent}", "%{Library.SPVRemapper}", "%{Library.glslang_ogl_compiler}", "%{Library.glslang_hlsl}", "%{Library.SPIRV_Cross_HLSL}", "pthread" }

	filter "configurations:Debug"
		defines { "HZ_DEBUG", "HZ_ENABLE_ASSERTS" }
		runtime "Debug"
		symbols "on"

		links
		{
			"%{Library.ShaderC_Debug}",
			"%{Library.SPIRV_Tools_Debug}",
			"%{Library.SPIRV-Tools-opt",
			"%{Library.glslang}",
			"%{Library.SPIRV_Cross_Debug}",
			"%{Library.SPIRV_Cross_GLSL_Debug}"
		}

	filter "configurations:Release"
		defines "HZ_RELEASE"
		runtime "Release"
		optimize "on"

		links
		{
			"%{Library.ShaderC_Release}",
			"%{Library.SPIRV_Cross_Release}",
			"%{Library.SPIRV_Cross_GLSL_Release}"
		}

	filter "configurations:Dist"
		defines "HZ_DIST"
		runtime "Release"
		optimize "on"

		links
		{
			"%{Library.ShaderC_Release}",
			"%{Library.SPIRV_Cross_Release}",
			"%{Library.SPIRV_Cross_GLSL_Release}"
		}

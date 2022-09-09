project "Hazelnut"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "off"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"src/**.h",
		"src/**.cpp",
		"%{IncludeDir.nfd}/nfd.hpp",
		"%{IncludeDir.nfd}/nfd.h"
	}

	includedirs
	{
		"%{wks.location}/Hazel/vendor/spdlog/include",
		"%{wks.location}/Hazel/src",
		"%{wks.location}/Hazel/vendor",
		"%{IncludeDir.glm}",
		"%{IncludeDir.entt}",
		"%{IncludeDir.ImGuizmo}",
		"%{IncludeDir.nfd}"
	}

	links
	{
		"Hazel", "Box2d", "GLFW", "Glad", "ImGui", "yaml-cpp", "nfd"
	}

	filter "system:windows"
		systemversion "latest"
	
	filter "system:linux"
		links { "GL", "X11", "dbus-1", "%{Library.ShaderC_Debug}", "%{Library.SPIRV_Cross_Debug}", "%{Library.SPIRV_Cross_GLSL_Debug}", "%{Library.SPIRV_Tools_Debug}", "%{Library.SPIRV_Tools_opt}", "%{Library.glslang}", "%{Library.glslang_code_gen}", "%{Library.glslang_machine_independent}", "%{Library.SPIRV_Cross_Util}", "%{Library.glslang_spirv}", "%{Library.glslang_default_resource_limits}", "%{Library.glslang_os_dependent}", "%{Library.SPVRemapper}", "%{Library.glslang_ogl_compiler}", "%{Library.glslang_hlsl}", "%{Library.SPIRV_Cross_HLSL}", "pthread" }
		libdirs { "/usr/lib" }

	filter "configurations:Debug"
		defines "HZ_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "HZ_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "HZ_DIST"
		runtime "Release"
		optimize "on"

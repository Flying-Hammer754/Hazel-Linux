project "Sandbox"
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
		"%{IncludeDir.nfd}"
	}

	links
	{
		"Hazel", "Box2d", "GLFW", "Glad", "ImGui", "nfd"
	}

	filter "system:windows"
		systemversion "latest"

	filter "system:linux"
		links { "GL", "X11", "dbus-1" }
		libdirs { "/usr/lib" }
		removefiles { "%{wks.location}/Hazel/vendor/nativefiledialog-extended/src/nfd_gtk.cpp" }

	filter "configurations:Debug"
		defines "HZ_DEBUG"
		runtime "Debug"
		symbols "on"
		links { "%{Library.ShaderC_Debug}", "%{Library.SPIRV_Cross_Debug}", "%{Library.SPIRV_Cross_GLSL_Debug}", "%{Library.SPIRV_Tools_Debug}" }

	filter "configurations:Release"
		defines "HZ_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "HZ_DIST"
		runtime "Release"
		optimize "on"

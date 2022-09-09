project "nfd"
    location "nativefiledialog-extended"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    includedirs { "nativefiledialog-extended/src/include" }
    files { "nativefiledialog-extended/src/include/*" }

    filter "system:windows"
        files { "nativefiledialog-extended/src/nfd_win.cpp" }
    filter "system:linux"
        includedirs { "/usr/include/dbus-1.0", "/usr/lib32/dbus-1.0/include", "/usr/lib/x86_64-linux-gnu" }
        files { "nativefiledialog-extended/src/nfd_portal.cpp" }
        links { "dbus-1" }

workspace "walnut"
  architecture "x64"

  configurations {
    "Debug",
    "Release",
    "Dist"
  }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "walnut"
  location "walnut"
  kind "SharedLib"
  language "C++"
  cppdialect "C++17"
  staticruntime "On"

  targetdir ("bin/" .. outputdir .. "/%{prj.name}")
  objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

  files {
    "%{prj.name}/src/**.h",
    "%{prj.name}/src/**.cpp",
  }

  includedirs {
    "%{prj.name}/vendor/spdlog/include"
  }

  defines {
    "WN_BUILD_DLL",
  }

  postbuildcommands {
    ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/player")
  }

  filter "system:macosx"
    defines {
      "WN_PLATFORM_MACOS"
    }

  filter "system:linux"
    defines {
      "WN_PLATFORM_LINUX"
    }

  filter "configurations:Debug"
    defines "WN_DEBUG"
    symbols "On"

  filter "configurations:Release"
    defines "WN_RELEASE"
    optimize "On"

  filter "configurations:Release"
    defines "WN_DIST"
    optimize "On"

project "player"
  location "player"
  kind "ConsoleApp"
  language "C++"
  cppdialect "C++17"
  staticruntime "On"

  targetdir ("bin/" .. outputdir .. "/%{prj.name}")
  objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

  files {
    "%{prj.name}/src/**.h",
    "%{prj.name}/src/**.cpp",
  }

  includedirs {
    "walnut/vendor/spdlog/include",
    "walnut/src",
  }

  links {
    "walnut"
  }

  filter "system:macosx"
    defines {
      "WN_PLATFORM_MACOS"
    }

  filter "system:linux"
    defines {
      "WN_PLATFORM_LINUX"
    }

  filter "configurations:Debug"
    defines "WN_DEBUG"
    symbols "On"

  filter "configurations:Release"
    defines "WN_RELEASE"
    optimize "On"

  filter "configurations:Release"
    defines "WN_DIST"
    optimize "On"

project "sandbox"
  location "sandbox"
  kind "SharedLib"
  language "C++"
  cppdialect "C++17"
  staticruntime "On"
  targetname ("sandbox-$$(date)")

  targetdir ("bin/" .. outputdir .. "/%{prj.name}")
  objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

  files {
    "%{prj.name}/src/**.h",
    "%{prj.name}/src/**.cpp",
  }

  includedirs {
    "walnut/vendor/spdlog/include",
    "walnut/src",
  }

  links {
    "walnut"
  }

  filter "system:macosx"
    defines {
      "WN_PLATFORM_MACOS"
    }

  filter "system:linux"
    defines {
      "WN_PLATFORM_LINUX"
    }

  filter "configurations:Debug"
    defines "WN_DEBUG"
    symbols "On"

  filter "configurations:Release"
    defines "WN_RELEASE"
    optimize "On"

  filter "configurations:Release"
    defines "WN_DIST"
    optimize "On"

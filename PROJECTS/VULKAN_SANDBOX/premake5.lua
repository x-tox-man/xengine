-- premake5.lua
workspace "VKSandbox"
	configurations { "Debug-VK", "Release-VK" }
	platforms { "Win32" }

project "VKSandbox"
	kind "WindowedApp"
	language "C++"
	targetdir "bin/%{cfg.buildcfg}"
	libdirs { "C:/VulkanSDK/1.0.65.1/Lib" }
	flags { "StaticRuntime" }
	defines { "__X_APP__" }

	files {
		"CODE/**.h",
		"CODE/**.cpp",
		"../../CODE/**.h",
		"../../CODE/**.hpp",
		"../../CODE/**.cpp",
		"../../CODE/**.c" }
	
	links { "libpng16", "liblua", "libuv", "zlib" }
	
	filter { "platforms:Win32" }
		system "Windows"
		architecture "x86"
		flags { "Maps", "MultiProcessorCompile", "NoImplicitLink", "NoImportLib", "NoIncrementalLink", "NoManifest", "NoRuntimeChecks", "WinMain" }
		defines { "__PLATFORM_WINDOWS__", "__AUDIO_OPENAL__", "_USE_MATH_DEFINES", "WIN32", "_WINDOWS" }
		links { "OpenAL32", "kernel32", "Userenv", "freetype262", "ws2_32","user32","gdi32","winspool","comdlg32","advapi32","shell32","ole32", "oleaut32","uuid", "odbc32", "odbccp32", "Iphlpapi", "Psapi" }
		removefiles { "../../CODE/**/*_OSX.h", "../../CODE/**/*_LINUX.*", "../../CODE/**/*_IOS.*", "../../CODE/**/*_POSIX.*", "../../CODE/TOOLS/**.*", "../../CODE/**/*OPENSL*",  "../../CODE/**/*ANDROID*" }
		includedirs {
			"../../CODE/**",
			"XCODE/GAME-ENGINE",
			"XCODE/GAME-ENGINE/**",
			"../../LIBRARY/WINDOWS/INCLUDES/LUA",
			"../../LIBRARY/WINDOWS/INCLUDES/PNG",
			"../../LIBRARY/WINDOWS/INCLUDES/UV",
			"../../LIBRARY/WINDOWS/INCLUDES/Z" ,
			"../../LIBRARY/WINDOWS/INCLUDES/OPENAL",
			"../../LIBRARY/WINDOWS/INCLUDES/FREETYPE"
			}
			
	filter { "platforms:Win32", "configurations:*GL4" }
		defines { "GL_GLEXT_PROTOTYPES", "GLEW_STATIC" }
		links { "OpenGL32", "glew32s", "glew32", "GlU32" }
		includedirs {
			"../../LIBRARY/WINDOWS/INCLUDES/GL"
			}
		
	filter { "platforms:Win32", "configurations:*GLES2" }
		defines {  }
		links {  }
	filter { "platforms:Win32", "configurations:Debug*" }
		libdirs { "../../LIBRARY/WINDOWS/DEBUG" }
	filter { "platforms:Win32", "configurations:Release*" }
		libdirs { "../../LIBRARY/WINDOWS/RELEASE" }
		
	filter "platforms:Unix"
		system "linux"
		architecture "x86_64"
		removefiles { "**WINDOWS*", "**OSX*", "**IOS*" }
	
	filter "configurations:*VK"
		removefiles { "../../CODE/**/*DX12*", "../../CODE/**/*GLES*", "../../CODE/**/*OPENGL*", "../../CODE/**/*OES2*", "../../CODE/**/*GL2*", "../../CODE/**/*GL3*", "../../CODE/**/*GL4*" }
		defines { "X_VK=1", "VK_USE_PLATFORM_WIN32_KHR" }
		sysincludedirs { "C:/VulkanSDK/1.0.65.1/Include" }
		links { "shaderc_combined", "VkLayer_screenshot", "VkLayer_monitor", "VkLayer_api_dump", "vulkan-1", "VkLayer_unique_objects", "VkLayer_threading", "VkLayer_parameter_validation", "VkLayer_object_tracker", "VkLayer_core_validation", "VkLayer_utils", "VKstatic.1" }

	filter "configurations:Debug*"
		defines { "DEBUG", "_DEBUG" }
		flags { "Symbols" }
		removefiles { "../../CODE/**/*COLLADA*.*" }

	filter "configurations:Release*"
		defines { "NDEBUG" }
		optimize "On"
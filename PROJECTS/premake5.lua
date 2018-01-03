-- premake5.lua
workspace "EngineLib"
	configurations { "Debug-VK", "Release-VK", "Debug-DX12", "Release-DX12", "Debug-GL4", "Release-GL4", "Debug-GLES2", "Release-GLES2", "ResourceBuilder", "unit-test" }
	platforms { "Win32" }

project "EngineLib"
	kind "StaticLib"
	language "C++"
	targetdir "bin/%{cfg.buildcfg}"
	libdirs { "libs", "../mylibs" }
	flags { "StaticRuntime" }
	defines { "__X_APP__" }

	files {
		"../CODE/**.h",
		"../CODE/**.hpp",
		"../CODE/**.cpp",
		"../CODE/**.c" }
	
	links { "libpng16", "liblua", "libuv", "zlib", "LinearMath", "Bullet3Collision", "Bullet3Common", "Bullet3Geometry", "Bullet3Dynamics", "BulletCollision", "BulletDynamics", "BulletInverseDynamics", "BulletInverseDynamicsUtils", "BulletSoftBody" }
	
	filter { "platforms:Win32" }
		system "Windows"
		architecture "x86"
		flags { "Maps", "MultiProcessorCompile", "NoImplicitLink", "NoImportLib", "NoIncrementalLink", "NoManifest", "NoRuntimeChecks", "WinMain" }
		defines { "__PLATFORM_WINDOWS__", "__AUDIO_OPENAL__", "_USE_MATH_DEFINES", "WIN32", "_WINDOWS", "__BULLET_PHYSICS__" }
		links { "OpenAL32", "kernel32", "Userenv", "EFX-Util", "freetype262", "ws2_32","user32","gdi32","winspool","comdlg32","advapi32","shell32","ole32", "oleaut32","uuid", "odbc32", "odbccp32", "Iphlpapi", "Psapi" }
		removefiles { "../CODE/**/*_OSX.h", "../CODE/**/*_LINUX.*", "../CODE/**/*_IOS.*", "../CODE/**/*_POSIX.*", "../CODE/TOOLS/MATH_TOOLBOX/**.*", "../CODE/TOOLS/FONT_EDITOR/**.*", "../CODE/TOOLS/ASSET_COMPILER/**.*", "../CODE/**/*OPENSL*",  "../CODE/**/*ANDROID*" }
		includedirs {
			"../CODE/**",
			"../LIBRARY/COMMON/BULLET/src/**",
			"../LIBRARY/COMMON/BULLET/src",
			"../LIBRARY/WINDOWS/INCLUDES/LUA",
			"../LIBRARY/WINDOWS/INCLUDES/PNG",
			"../LIBRARY/WINDOWS/INCLUDES/UV",
			"../LIBRARY/WINDOWS/INCLUDES/Z" ,
			"../LIBRARY/WINDOWS/INCLUDES/OPENAL",
			"../LIBRARY/WINDOWS/INCLUDES/FREETYPE"
			}
			
	filter { "platforms:Win32", "configurations:*GL4" }
		defines { "GL_GLEXT_PROTOTYPES", "GLEW_STATIC" }
		links { "OpenGL32", "glew32s", "glew32", "GlU32" }
		includedirs {
			"../LIBRARY/WINDOWS/INCLUDES/GL"
			}
		
	filter { "platforms:Win32", "configurations:*GLES2" }
		defines {  }
		links {  }
	filter { "platforms:Win32", "configurations:Debug*" }
		libdirs { "../LIBRARY/WINDOWS/DEBUG" }
	filter { "platforms:Win32", "configurations:Release*" }
		libdirs { "../LIBRARY/WINDOWS/RELEASE" }
		
	filter { "platforms:macosx", "configurations:Debug*" }
		libdirs { "../LIBRARY/OSX/DEBUG" }
	filter { "platforms:macosx", "configurations:Release*" }
		libdirs { "../LIBRARY/OSX/RELEASE" }
		
	filter { "platforms:macosx" }
		system "macosx"
		architecture "x86_64"
		defines { "__COMPILE_WITH_COLLADA__", "OPENGL3=1", "__PLATFORM_OSX__", "__AUDIO_OPENAL__" }
		includedirs{ "../LIBRARY/OSX/INCLUDES/LUA", "../LIBRARY/OSX/INCLUDES/PNG", "../LIBRARY/OSX/INCLUDES/UV", "../LIBRARY/OSX/INCLUDES/Z" }
		removefiles { "**WINDOWS.*", "**LINUX.*", "**IOS.*" }
		files {
			"XCODE/GAME-ENGINE-REBORN/main.m",
			"XCODE/GAME-ENGINE-REBORN/AppDelegate.h",
			"XCODE/GAME-ENGINE-REBORN/AppDelegate.m" }
		
	filter "platforms:Unix"
		system "linux"
		architecture "x86_64"
		removefiles { "**WINDOWS*", "**OSX*", "**IOS*" }
	
	filter "configurations:*GL4"
		removefiles { "../CODE/**/*DX12*", "../CODE/**/*GLES*", "../CODE/**/*OES2*" }
		defines { "OPENGL4=1" }
		
	filter "configurations:*GLES2"
		removefiles { "../CODE/**/*DX12*", "../CODE/**/*GL2*", "../CODE/**/*GL3*", "../CODE/**/*GL4*" }
		defines { "OPENGLES2=1" }
		
	filter "configurations:*DX12"
		removefiles { "../CODE/**/*GLES*", "../CODE/**/*GL2*", "../CODE/**/*GL3*", "../CODE/**/*GL4*" }
		defines { "DIRECTX12=1" }
		
	filter "configurations:*VK"
		removefiles { "../CODE/**/*DX12*", "../CODE/**/*GLES*", "../CODE/**/*OPENGL*", "../CODE/**/*OES2*", "../CODE/**/*GL2*", "../CODE/**/*GL3*", "../CODE/**/*GL4*" }
		defines { "X_VK=1" }
		sysincludedirs {
			"C:/VulkanSDK/1.0.39.1/Include"
			}

	filter "configurations:Debug*"
		defines { "DEBUG", "_DEBUG" }
		flags { "Symbols" }
		removefiles { "../CODE/**/*COLLADA*.*" }

	filter "configurations:Release*"
		defines { "NDEBUG" }
		optimize "On"
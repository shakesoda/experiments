solution "EmuGB"
configurations { "Debug" }

project "EmuGB"
	targetname "emu-gb"
	kind "ConsoleApp"
	language "C"
	files { "src/**.c" }
	includedirs { "src/" }
	defines { "USING_MAKEFILE" }
	buildoptions { "-Wall", "-pedantic" }

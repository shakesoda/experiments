solution "underwater programmer boxing"
configurations { "Debug", "Release" }

configuration "Debug"
	targetsuffix "-d"

configuration { "linux", "gmake", "Debug" }
	buildoptions { "-ggdb" }

include "lib/tinythread"
include "lib/glfw"
include "lib/assimp"
include "lib/physfs"
include "lib/zlib"
include "lib/gl3w"
include "lib/lua"

project "Nepgear" 
	targetname "nepgear"
	targetdir "bin"
	kind "ConsoleApp"
	language "C++"
	files { "src/**.cpp" }
	libdirs { "bin" }
	links {
		"pthread", "TinyThread++",
		"GLFW", "Xrandr", "X11", "GL",
		"Assimp", "PhysFS", "ZLib", "GL3W",
		"Lua"
	}
	includedirs {
		"lib/glfw/include",
		"lib/assimp/include",
		"lib/gl3w/include",
		"lib/glm",
		"lib/physfs",
		"lib/zlib",
		"lib/tinythread",
		"lib/lua/src",
		"src"
	}

	configuration { "linux", "gmake" }
		buildoptions { "-std=c++0x", "-Wall", "-pedantic", "-Werror", "-Wextra" }

	configuration { "linux", "codelite" }
		buildoptions { "-std=c++0x", "-Wall", "-pedantic", "-Werror", "-Wextra" }

	configuration { "linux", "gmake", "Debug" }
		buildoptions { "-ggdb" }

-- TODO
newaction {
	trigger     = "install",
	description = "Install Nepgear (NOT IMPLEMENTED)",
	execute = function ()
		-- copy files, etc. here
	end
 }
 
#include "Lua.h"
namespace Grind
{
	Lua::Lua()
	{
		L = lua_open();
		
		//type *something = (type*)lua_touserdata(L, 1);
	}

	Lua::~Lua()
	{
		lua_close(L);
	}

	void Lua::initialise()
	{
		// register crap here, load init scripts, etc.
	}
}

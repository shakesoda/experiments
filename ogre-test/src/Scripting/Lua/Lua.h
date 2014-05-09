#ifndef  _GRIND_LUA_H_
#define _GRIND_LUA_H_

extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

namespace Grind
{
	class Lua
	{
	public:
		Lua();
		virtual ~Lua();
		
		void initialise();
	private:
		lua_State *L;
	};
}

#endif

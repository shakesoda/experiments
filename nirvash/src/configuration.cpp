#include "configuration.h"

namespace Nepgear
{
 
Configuration::Configuration(std::string file)
{
	L = lua_open();

	luaL_Reg libs[] =
	{
		{ "base",	luaopen_base },
//		{ "table",	luaopen_table },
		{ "string",	luaopen_string },
		{ "math",	luaopen_math },
//		{ "debug",	luaopen_debug },
		//{ "io",	luaopen_io },
		//{ "os",	luaopen_os },
		//{ "package", luaopen_package },
		{ NULL, NULL }
	};

	const luaL_reg *lib = libs;
	for ( ; lib->func; lib++)
	{
		// open library
		lib->func(L);

		// discard any results
		lua_settop(L, 0);
	}

	luaL_loadfile(L, file.c_str());

	if (lua_pcall(L, 0, 0, 0))
	{
		printf("[Configuration] %s\n", lua_tostring(L, -1));
		lua_pop(L, 1);
		return;
	}
}

Configuration::~Configuration()
{
	lua_close(L);
}

int Configuration::get_integer(std::string key, int fallback)
{
	int tmp = fallback;
	lua_getfield(L, LUA_GLOBALSINDEX, key.c_str());
	if (lua_isnumber(L, 1))
		tmp = lua_tointeger(L, 1);
	else
		tmp = fallback;
	lua_pop(L, 1);

	return tmp;
}

std::string Configuration::get_string(std::string key, std::string fallback)
{
	std::string tmp = fallback;
	lua_getfield(L, LUA_GLOBALSINDEX, key.c_str());
	if (lua_isstring(L, 1))
		tmp = std::string(lua_tostring(L, 1));
	lua_pop(L, 1);

	return tmp;
}

double Configuration::get_number(std::string key, double fallback)
{
	double tmp = fallback;
	lua_getfield(L, LUA_GLOBALSINDEX, key.c_str());
	if (lua_isnumber(L, 1))
		tmp = (double)lua_tonumber(L, 1);
	lua_pop(L, 1);

	return tmp;
}

bool Configuration::get_boolean(std::string key, bool fallback)
{
	bool tmp = fallback;
	lua_getfield(L, LUA_GLOBALSINDEX, key.c_str());
	if (lua_isboolean(L, 1))
		tmp = (bool)lua_toboolean(L, 1);
	lua_pop(L, 1);

	return tmp;
}

}

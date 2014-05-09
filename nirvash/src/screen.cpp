#include "screen.h"
#include <ostream>
#include <sstream>
#include <unistd.h>

namespace Nepgear
{

Screen::Screen(std::string _name, void *_data)
{
	name = _name;
	data = _data;
}

Screen::~Screen()
{
	// TODO
}

void Screen::load(const State *ng)
{
	int err = 0;
	std::ostringstream file;
	file << "game/" << name << ".lua";

	if (access(file.str().c_str(), F_OK))
	{
		printf("File %s doesn't exist.\n", file.str().c_str());
		return;
	}

	luaL_loadfile(ng->lua, file.str().c_str());

	err = lua_pcall(ng->lua, 0, 0, 0);
	if (err)
	{
		switch (err)
		{
			case LUA_ERRRUN: printf("Lua: runtime error\n"); break;
			case LUA_ERRMEM: printf("Lua: memory allocation error\n"); break;
			default: break;
		}
		lua_pop(ng->lua, 1);
	}
}

void Screen::update(double dt)
{
	UNUSED(dt);
}

void Screen::draw()
{
}

void Screen::input(const GameInput *gi)
{
	UNUSED(gi);
}

}

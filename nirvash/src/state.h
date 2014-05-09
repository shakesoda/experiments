#ifndef _NEPGEAR_STATE_H_
#define _NEPGEAR_STATE_H_

#include "utils/thread.h"
#include "window.h"
#include "inputstate.h"
#include <map>
#include <vector>

extern "C"
{
	#include "lua.h"
	#include "lualib.h"
	#include "lauxlib.h"
}

// Nepgear/state.h
namespace Nepgear
{
	struct State
	{
		State() : start(false), running(true) {}

		Mutex lock;

		std::map<std::string, Thread*> threads;
		std::vector<Window*> windows;

		std::map<std::string, bool> configuration;

		InputState input;

		lua_State *lua;

		bool start;
		bool running;
	};
}

#define UNUSED(x) ((void)(x)) /* to avoid warnings */

#endif

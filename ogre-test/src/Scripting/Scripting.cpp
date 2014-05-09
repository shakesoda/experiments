#include "Scripting.h"
#include "Lua.h"

namespace Grind
{
	void ScriptManager::initialise()
	{
		mLua.initialise();
	}

	void ScriptManager::shutdown()
	{
		// nothing
	}

	Lua *ScriptManager::getLua()
	{
		return &mLua;
	}
}

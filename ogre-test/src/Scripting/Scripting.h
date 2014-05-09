#ifndef _SCRIPTING_H_
#define _SCRIPTING_H_

#include "Lua.h"
#include "Singleton.h"

namespace Grind
{
	class ScriptManager : public Singleton<ScriptManager>
	{
	public:
		void initialise();
		void shutdown();
		
		Lua *getLua();
		
	private:
		Lua mLua;
	};
}

#endif

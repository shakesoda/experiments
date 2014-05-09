#ifndef _NEPGEAR_CONFIGURATION_H_
#define _NEPGEAR_CONFIGURATION_H_

extern "C"
{
	#include "lua.h"
	#include "lualib.h"
	#include "lauxlib.h"
}

#include <string>

namespace Nepgear
{

class Configuration
{
public:
	Configuration(std::string file);
	virtual ~Configuration();

	int get_integer(std::string key, int fallback);
	std::string get_string(std::string key, std::string fallback);
	double get_number(std::string key, double fallback);
	bool get_boolean(std::string key, bool fallback);

private:
	lua_State *L;
};

}

#endif

#ifndef _NEPGEAR_SCREEN_H_
#define _NEPGEAR_SCREEN_H_

#include <string>
//#include "gameinput.h"
#include "state.h"

class GameInput;

namespace Nepgear
{
class Screen
{
public:
	Screen(std::string name, void *data = NULL);
	virtual ~Screen();

	std::string name;

	virtual void load(const State *ng);
	//virtual void quit();

	//virtual void focus();
	virtual void update(double dt);
	virtual void draw();

	virtual void input(const GameInput *gi);

	void *data;
	struct {
		std::string name;
		void *data;
	} next;
};
}

#endif

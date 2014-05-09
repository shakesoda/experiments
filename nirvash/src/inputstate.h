#ifndef _NEPGEAR_INPUT_STATE_H_
#define _NEPGEAR_INPUT_STATE_H_

#include <vector>
#include <glm/glm.hpp>

namespace Nepgear
{
struct State;

enum InputEventType {
	InputEventType_Mouse,

	// keyboard
	InputEventType_Key,

	// joystick
	InputEventType_Axis,
	InputEventType_Button,

	InputEventType_Invalid
};

struct InputEvent
{
	InputEvent(InputEventType t):
		coords(glm::vec2(0.0f,0.0f)), key(0),
		pressed(false), value(0.0f), type(t) { }

	// mouse/tablet/touch coords
	glm::vec2 coords;

	// keyboard key
	int key;

	// joystick button, axis
	bool pressed;
	float value;

	InputEventType type;
};

/*
 * Note: You should probably only have one of these.
 */

class InputState
{
public:
	void send(int key, int state);
	void poll_events(State *game);
private:
	std::vector<InputEvent> m_state;
	std::vector<InputEvent> m_queue;
};

}

#endif

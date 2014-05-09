#include "state.h"
#include <GL/glfw3.h>
#include <cstring>
#if 0
using namespace Nepgear;

namespace
{
	void build_queue(GLFWwindow window, int key, int state)
	{
		Nepgear::State* game = (Nepgear::State*)glfwGetWindowUserPointer(window);
		InputState *input = game->input;

		input->send(key, state);
	}

	int window_close(GLFWwindow window)
	{
		Nepgear::State *game = (Nepgear::State*)glfwGetWindowUserPointer(window);
		game->kill();
	}
}

void InputState::send(int key, int state)
{
	InputEvent evt(InputEventType_Key);
	evt.key = key;
	m_queue.push_back(evt);
}

void InputState::poll_events(NepgearState *game)
{
	GLFWwindow *window = (GLFWwindow*)
		game->display->GetRenderer().get_window();

	glfwSetWindowUserPointer(*window, game);
	glfwSetKeyCallback(&build_queue);

	glfwSetWindowCloseCallback(&window_close);

	glfwPollEvents();

	m_queue.clear();

	/* NOTE: I'm testing this on a macbook pro, and on linux the
	 * accelerometers register as /dev/input/js0. Testing with a PS3
	 * controller on js1. */
	for (int js = 0; js < GLFW_JOYSTICK_LAST; js++)
	{
		if (glfwGetJoystickParam(js, GLFW_PRESENT))
		{
			int num_axes = glfwGetJoystickParam(js, GLFW_AXES);
			int num_buttons = glfwGetJoystickParam(js, GLFW_BUTTONS);

			float *axes = new float[num_axes];
			unsigned char *buttons = new unsigned char[num_buttons];

			// read JS data
			glfwGetJoystickButtons(js, buttons, num_buttons);
			glfwGetJoystickPos(js, axes, num_axes);

			// convert to input struct so it's useful.
			for (int i = 0; i < num_axes; i++)
			{
				InputEvent evt(InputEventType_Axis);
				evt.value = axes[i];
				m_queue.push_back(evt);
			}

			for (int i = 0; i < num_buttons; i++)
			{
				InputEvent evt(InputEventType_Axis);
				evt.pressed = buttons[i] ? true : false;
				m_queue.push_back(evt);
			}

			for (int i = 0; i < num_axes; i++)
				printf("js%2i:%2i\t= %+2.3f\n", js, i, axes[i]);

			delete[] axes;
			delete[] buttons;
		}
	}

	while (!m_queue.empty())
	{
		InputEvent &evt = m_queue.back();
		if (evt.type == InputEventType_Key && evt.key == GLFW_KEY_ESCAPE)
			game->kill();
		m_queue.pop_back();
	}
}
#endif

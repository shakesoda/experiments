#include "timer.h"
#include <GL/glfw3.h>

using namespace Nepgear;

void Timer::touch()
{
	time.then = glfwGetTime();
}

double Timer::ago()
{
	return glfwGetTime() - time.then;
}

void Timer::calculate_delta()
{
	time.then = time.now;
	time.now = glfwGetTime();
	time.delta = time.now - time.then;
}

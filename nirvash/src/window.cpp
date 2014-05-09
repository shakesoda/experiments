#include "window.h"
#include <GL/gl3w.h>
#include <GL/glfw3.h>

// Nepgear/window.cpp
namespace Nepgear
{
	/* these may be better as static or something, since they don't respect
	 * objects but instead are thread-bound. */
	void Window::MakeCurrent()
	{
		glfwMakeContextCurrent((GLFWwindow)m_handle);
	}

	void Window::ClearCurrent()
	{
		glfwMakeContextCurrent(NULL);
	}

	WindowHandle Window::GetHandle()
	{
		return m_handle;
	}

	const WindowFlags Window::GetFlags()
	{
		return m_flags;
	}

	void Window::Create(WindowFlags flags)
	{
		int mode = (flags.mode == WindowFlags::FullScreen) ?
			GLFW_FULLSCREEN : GLFW_WINDOWED;

		if (flags.gl_major >= 3)
		{
			if (flags.strict)
			{
				glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
				glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, true);
			} else {
				glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
				glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, false);
			}
			glfwWindowHint(GLFW_OPENGL_VERSION_MAJOR, flags.gl_major);
			glfwWindowHint(GLFW_OPENGL_VERSION_MINOR, flags.gl_minor);
		}
		m_flags = flags;
		m_handle = (WindowHandle)glfwCreateWindow(
			flags.width, flags.height,
			mode, "", (GLFWwindow)flags.homie
		);
		glfwSetWindowUserPointer(m_handle, this);
		width = flags.width;
		height = flags.height;
	}

	void Window::Destroy()
	{
		glfwDestroyWindow((GLFWwindow)m_handle);
	}

	int Window::Prepare(int major, int minor)
	{
		// Don't bother if using GL2.
		if (major < 3) return true;
		gl3wInit();
		return gl3wIsSupported(major, minor);
	}

	void Window::VSync(bool enabled)
	{
		glfwSwapInterval((int)enabled);
	}

	void Window::SwapBuffers()
	{
		glfwSwapBuffers((GLFWwindow)m_handle);
	}
}

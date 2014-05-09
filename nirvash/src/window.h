#ifndef _NEPGEAR_WINDOW_H_
#define _NEPGEAR_WINDOW_H_

// Nepgear/window.h
namespace Nepgear
{
	typedef void* WindowHandle;

	struct WindowFlags
	{
		int width, height;
		int gl_major, gl_minor;
		bool strict;
		enum {
			FullScreen = 0,
			Windowed,
			Invalid
		} mode;
		WindowHandle *homie;
	};

	class Window
	{
	public:
		void Create(WindowFlags flags);
		void Destroy();
		void MakeCurrent();
		void ClearCurrent();

		//void Resize(glm::vec2);

		int Prepare(int major, int minor);
		void VSync(bool);
		void SwapBuffers();

		WindowHandle GetHandle();
		const WindowFlags GetFlags();

		int width, height;

	protected:
		WindowHandle m_handle;
		WindowFlags m_flags;
	};
}

#endif

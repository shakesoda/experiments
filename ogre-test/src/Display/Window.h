#ifndef _WINDOW_MANAGER_H_
#define _WINDOW_MANAGER_H_

#include <OGRE/OgreRoot.h>
#include <OGRE/OgreRenderSystem.h>
#include <OGRE/OgreRenderWindow.h>
#include "Singleton.h"

std::string getBundlePath();

namespace Grind
{
	class CheckWindowListener : public Ogre::FrameListener
	{
		bool frameStarted(const Ogre::FrameEvent &evt);
	};
	class WindowManager : public Singleton<WindowManager>
	{
	public:
		WindowManager();
		virtual ~WindowManager();
		
		bool initialise();
		void shutdown();
		void createWindow();
		
		Ogre::RenderSystem *r;
		Ogre::RenderWindow *window;
		Ogre::Root *root;
		
	protected:
		CheckWindowListener checkWindow;
		bool didShutdown;
	};
}

#endif

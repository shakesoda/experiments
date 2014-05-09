#include "Window.h"
#include "Game.h"
#include "CameraManager.h"

#ifdef __APPLE__
	#include <CoreFoundation/CoreFoundation.h>
#endif

std::string getBundlePath()
{
	std::string _path = "";
// For OS X, get stuff from the application bundle (where it is expected to reside)
#ifdef __APPLE__
	/*
	 * This function will locate the path to our application on OS X,
	 * unlike windows you cannot rely on the current working directory
	 * for locating your configuration files and resources.
	 */
	char path[1024];
	CFBundleRef mainBundle = CFBundleGetMainBundle();
	assert(mainBundle); // make sure nothing is terribly wrong here.
	CFURLRef mainBundleURL = CFBundleCopyBundleURL(mainBundle);
	CFStringRef cfStringRef = CFURLCopyFileSystemPath(mainBundleURL, kCFURLPOSIXPathStyle);
	CFStringGetCString(cfStringRef, path, 1024, kCFStringEncodingUTF8);
	CFRelease(mainBundleURL);
	CFRelease(cfStringRef);
	
	_path = path;
	_path += "/Contents/";
#endif
	return _path;
}

using namespace Ogre;

namespace Grind
{
	bool CheckWindowListener::frameStarted(const FrameEvent &evt)
	{
		if (WindowManager::getSingleton()->window->isClosed())
			return false;
		return true;
	}

	WindowManager::WindowManager() : didShutdown(false) { }

	WindowManager::~WindowManager()
	{
		shutdown();
	}

	bool WindowManager::initialise()
	{
		root = new Root();
		
		// Load OpenGL plugin
		root->loadPlugin(getBundlePath() + "Plugins/RenderSystem_GL");
		root->addResourceLocation(getBundlePath() + "Resources", "FileSystem");
		
		// List renderers
		RenderSystemList rs = root->getAvailableRenderers();
		
		// Make sure it loaded, get it, and set it as our renderer.
		if(rs.at(0)->getName().compare("RenderSystem_GL"))
		{
			r = rs.at(0);
			r->setConfigOption("Full Screen", "No");
			r->setConfigOption("FSAA", "2");
			r->setConfigOption("Video Mode", "720 x 480 @ 32-bit colour");
			root->setRenderSystem(r);
			
			return 1;
		}
		return 0;
	}

	void WindowManager::shutdown()
	{
		if (!didShutdown)
			root->shutdown();
	}

	void WindowManager::createWindow()
	{
		GameManager *game = GameManager::getSingleton();
		
		window = root->initialise(true, "OpenGrind");
		game->scene = root->createSceneManager(ST_GENERIC);
		
		ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
		
		CameraManager::getSingleton()->createCamera();
		
		// Get out of here if the window was closed!
		root->addFrameListener(&checkWindow);
	}
}

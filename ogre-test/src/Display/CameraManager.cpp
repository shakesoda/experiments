#include "Game.h"
#include "Window.h"
#include "CameraManager.h"

#include <OGRE/OgreSceneManager.h>
#include <OGRE/OgreCamera.h>

using namespace Ogre;

namespace Grind
{
	void CameraManager::createCamera()
	{
		GameManager *game = GameManager::getSingleton();
		WindowManager *wnd = WindowManager::getSingleton();
		
		m_camera = game->scene->createCamera("ChaseCamera");
		m_camera->setFOVy(Degree(60));
		m_camera->setNearClipDistance(15);
		m_camera->setFarClipDistance(5000);
		
		Viewport *vp = wnd->window->addViewport(m_camera);
		vp->setBackgroundColour(ColourValue(0.25, 0.25, 0.25));
		m_camera->setAspectRatio(Real(vp->getActualWidth())/Real(vp->getActualHeight()));
	}

	Camera *CameraManager::getCamera()
	{
		return m_camera;
	}
}

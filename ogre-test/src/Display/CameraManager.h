#ifndef _GRIND_CAMERA_MANAGER_H_
#define _GRIND_CAMERA_MANAGER_H_

#include "CameraManager.h"
#include "Singleton.h"

#include <OGRE/OgreCamera.h>

namespace Grind
{
	class CameraManager : public Singleton<CameraManager>
	{
	public:
		void createCamera();
		
		Ogre::Camera *getCamera();

	private:
		
		Ogre::Camera *m_camera;
	};
}
#endif

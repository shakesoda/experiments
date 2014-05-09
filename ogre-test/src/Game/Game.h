#ifndef _GRIND_GAME_MANAGER_H_
#define _GRIND_GAME_MANAGER_H_

#include <OGRE/OgreSceneManager.h>
#include "Singleton.h"

namespace Grind
{
	class GameManager : public Singleton<GameManager>
	{
	public:
		GameManager() { }
		virtual ~GameManager() { }
		
		Ogre::SceneManager *scene;
	};
}

#endif

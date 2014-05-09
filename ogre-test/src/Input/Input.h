#ifndef _INPUT_MANAGER_H_
#define _INPUT_MANAGER_H_

#include "Singleton.h"
#include <OIS/OIS.h>
#include <OGRE/OgreFrameListener.h>

namespace Grind
{
	class InputManager : public Singleton<InputManager>
	{
	public:
		InputManager();
		virtual ~InputManager();
		
		void initialise();
		
	protected:
		class listener : public Ogre::FrameListener
		{
			bool frameStarted(const Ogre::FrameEvent &evt);
		public:
			InputManager *input;
		};

		OIS::InputManager	*m_InputManager;
		
	public:
		OIS::Mouse			*m_Mouse;
		OIS::Keyboard		*m_Keyboard;

		listener m_Listener;
	};
}

#endif

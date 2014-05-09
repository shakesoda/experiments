#include "Input.h"
#include <iostream>
#include "Window.h"

namespace Grind
{
	InputManager::InputManager() {}
	InputManager::~InputManager() {}
	
	void InputManager::initialise()
	{
		// Get window handle and use it to init OIS.
		size_t hWnd = 0;
		WindowManager *wnd = WindowManager::getSingleton();
		
		wnd->window->getCustomAttribute("WINDOW", &hWnd);
		m_InputManager = OIS::InputManager::createInputSystem(hWnd);
		
		// Create mouse + keyboard device handles.
		m_Mouse = (OIS::Mouse*)m_InputManager->createInputObject(OIS::OISMouse, false);
		m_Keyboard = (OIS::Keyboard*)m_InputManager->createInputObject(OIS::OISKeyboard, false);

		m_Listener.input = this;
	}
	
	bool InputManager::listener::frameStarted(const Ogre::FrameEvent &evt)
	{
		input->m_Keyboard->capture();
		if (input->m_Keyboard->isKeyDown(OIS::KC_ESCAPE))
			return false;
				
		return true;
	}
}

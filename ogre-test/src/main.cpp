#include <string>
#include <iostream>

#include "Scripting.h"
#include "Window.h"
#include "Game.h"

#include <OGRE/OgreOverlay.h>
#include <OGRE/OgreSceneNode.h>
#include <OGRE/OgreEntity.h>
#include <OIS/OIS.h>

#include "CameraManager.h"
#include "Input.h"

using namespace Ogre;
using namespace Grind;

class rotator : public FrameListener
{
public:
	void setKeyboard(OIS::Keyboard *kb) { m_Keyboard = kb; }
	void setMouse(OIS::Mouse *mouse) { m_Mouse = mouse; }
	void setCamera(Camera *cam) { m_Camera = cam; }
protected:
	bool frameStarted(const Ogre::FrameEvent &evt)
	{
		m_Mouse->capture();
		OIS::MouseState state = m_Mouse->getMouseState();
		
		m_Camera->pitch(-Radian(state.Y.rel/200.f));
		m_Camera->yaw(-Radian(state.X.rel/200.f));
		
		m_Keyboard->capture();
		
		// forward
		if (m_Keyboard->isKeyDown(OIS::KC_W))
			m_Camera->setPosition(m_Camera->getPosition() + m_Camera->getDirection());
		
		// backward
		if (m_Keyboard->isKeyDown(OIS::KC_S))
			m_Camera->setPosition(m_Camera->getPosition() - m_Camera->getDirection());
		
		// left
		if (m_Keyboard->isKeyDown(OIS::KC_A))
			m_Camera->setPosition(m_Camera->getPosition() - m_Camera->getRight());
		
		// right
		if (m_Keyboard->isKeyDown(OIS::KC_D))
			m_Camera->setPosition(m_Camera->getPosition() + m_Camera->getRight());
		
		return true;
	}
	Camera *m_Camera;
	OIS::Mouse *m_Mouse;
	OIS::Keyboard *m_Keyboard;
};

int main(int argc, char **argv)
{
	Grind::WindowManager *wnd	 = Grind::WindowManager::getSingleton();
	Grind::GameManager	 *game	 = Grind::GameManager::getSingleton();
	Grind::InputManager	 *input	 = Grind::InputManager::getSingleton();
	Grind::ScriptManager *script = Grind::ScriptManager::getSingleton();

	// Oh no! Couldn't create a window.
	if (!wnd->initialise())
		return 1;
	
	wnd->createWindow();
	script->initialise();
	input->initialise();
	
	Camera *cam = Grind::CameraManager::getSingleton()->getCamera();
	cam->setPosition(0, 25, 40);
	cam->lookAt(0, 20, 20);
	
	// lazy + ugly
#define LOAD(n, p) game->scene->createEntity(n, p)
	Entity *shibuya			= LOAD("Shibuya", "shibuya_terminal.mesh");
	Entity *beat			= LOAD("Beat", "beat.mesh");
#undef LOAD

	SceneNode *root = game->scene->getRootSceneNode();
	
	SceneNode *shibuyaNode = root->createChildSceneNode("ShibuyaNode");
	shibuyaNode->attachObject(shibuya);
	shibuyaNode->setScale(-1,1,1);
	
	SceneNode *beatNode = root->createChildSceneNode("BeatNode");
	beatNode->attachObject(beat);
	beatNode->setPosition(0, -2, 0);
	
	rotator *foo = new rotator();
	foo->setCamera(cam);
	foo->setKeyboard(input->m_Keyboard);
	foo->setMouse(input->m_Mouse);
	
	wnd->root->addFrameListener(foo);
	
	wnd->root->addFrameListener(&input->m_Listener);
	wnd->root->startRendering();
	
	delete foo;
	
	// time to go
	script->shutdown();
	
	return 0;
}

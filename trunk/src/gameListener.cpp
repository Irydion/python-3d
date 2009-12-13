#include "gameListener.h"

GameListener::GameListener(Ogre::SceneManager *sceneMgr, OIS::Keyboard *keyboard, OIS::Mouse *mouse)
{
	_SceneManager = sceneMgr;

	_Keyboard = keyboard;
	_Mouse = mouse;

    _Keyboard->setEventCallback(this);
    _Mouse->setEventCallback(this);

	_Continue = true;
}

GameListener::~GameListener()
{
}

bool GameListener::frameStarted(const Ogre::FrameEvent &evt)
{
	_Keyboard->capture();
	_Mouse->capture();

	return _Continue;
}

bool GameListener::keyPressed(const OIS::KeyEvent &e)
{
	return true;
}

bool GameListener::keyReleased(const OIS::KeyEvent &e)
{
	switch (e.key)
    {
        case OIS::KC_ESCAPE:
            _Continue = false;
            break;

        default:
			;
    }

    return true;
}

bool GameListener::mouseMoved(const OIS::MouseEvent &e)
{
	return true;
}

bool GameListener::mousePressed(const OIS::MouseEvent &e, OIS::MouseButtonID id)
{
	return true;
}

bool GameListener::mouseReleased(const OIS::MouseEvent &e, OIS::MouseButtonID id)
{
	return true;
}

#include "gameListener.h"

GameListener::GameListener()
{
}

GameListener::~GameListener()
{
}

bool GameListener::frameStarted(const Ogre::FrameEvent &evt)
{
	return true;
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
            return false;
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

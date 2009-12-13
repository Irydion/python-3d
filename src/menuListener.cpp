#include "menuListener.h"

MenuListener::MenuListener()
{
}

MenuListener::~MenuListener()
{
}

bool MenuListener::frameStarted(const Ogre::FrameEvent &evt)
{
	return true;
}

bool MenuListener::keyPressed(const OIS::KeyEvent &e)
{
	return true;
}

bool MenuListener::keyReleased(const OIS::KeyEvent &e)
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

bool MenuListener::mouseMoved(const OIS::MouseEvent &e)
{
	return true;
}

bool MenuListener::mousePressed(const OIS::MouseEvent &e, OIS::MouseButtonID id)
{
	return true;
}

bool MenuListener::mouseReleased(const OIS::MouseEvent &e, OIS::MouseButtonID id)
{
	return true;
}

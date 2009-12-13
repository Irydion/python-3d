#include "eventListener.h"

EventListener::EventListener(Ogre::SceneManager *sceneMgr, OIS::Keyboard *keyboard, OIS::Mouse *mouse)
{
	_SceneManager = sceneMgr;

	_Keyboard = keyboard;
	_Mouse = mouse;

	gameListener = new GameListener();
	menuListener = new MenuListener();

    _Keyboard->setEventCallback(this);
    _Mouse->setEventCallback(this);

	_Continue = true;
	_Actif = 0;
}

EventListener::~EventListener()
{
}

bool EventListener::frameStarted(const Ogre::FrameEvent &evt)
{
	_Keyboard->capture();
	_Mouse->capture();

	switch(_Actif)
	{
		case 0:
			gameListener->frameStarted(evt);
			break;
		case 1:
			menuListener->frameStarted(evt);
			break;
	}

	return _Continue;
}

bool EventListener::keyPressed(const OIS::KeyEvent &e)
{
	switch(_Actif)
	{
		case 0:
			_Continue = gameListener->keyPressed(e);
			break;
		case 1:
			_Continue = menuListener->keyPressed(e);
			break;
	}

	return true;
}

bool EventListener::keyReleased(const OIS::KeyEvent &e)
{
	switch(_Actif)
	{
		case 0:
			_Continue = gameListener->keyReleased(e);
			break;
		case 1:
			_Continue = menuListener->keyReleased(e);
			break;
	}

    return true;
}

bool EventListener::mouseMoved(const OIS::MouseEvent &e)
{
	switch(_Actif)
	{
		case 0:
			_Continue = gameListener->mouseMoved(e);
			break;
		case 1:
			_Continue = menuListener->mouseMoved(e);
			break;
	}

	return true;
}

bool EventListener::mousePressed(const OIS::MouseEvent &e, OIS::MouseButtonID id)
{
	switch(_Actif)
	{
		case 0:
			_Continue = gameListener->mousePressed(e, id);
			break;
		case 1:
			_Continue = menuListener->mousePressed(e, id);
			break;
	}

	return true;
}

bool EventListener::mouseReleased(const OIS::MouseEvent &e, OIS::MouseButtonID id)
{
	switch(_Actif)
	{
		case 0:
			_Continue = gameListener->mouseReleased(e, id);
			break;
		case 1:
			_Continue = menuListener->mouseReleased(e, id);
			break;
	}

	return true;
}

/*
-------------------------------------------------------------------------------
This file is part of Python3D.

Copyright (c) 2009-2010 Emilien Dupont
Also see acknowledgements in COPYING.txt

Python3D is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Python3D is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Python3D. If not, see <http://www.gnu.org/licenses/>.
-------------------------------------------------------------------------------
*/

#include "eventListener.h"

EventListener::EventListener(Ogre::SceneManager *sceneMgr, Ogre::RenderWindow *renderWindow, OIS::Keyboard *keyboard, OIS::Mouse *mouse, CEGUI::System *GUISystem, CEGUI::OgreCEGUIRenderer *GUIRenderer, Snake *snake)
{
	_SceneManager = sceneMgr;
	_RenderWindow = renderWindow;

	_Keyboard = keyboard;
	_Mouse = mouse;

	_GUISystem = GUISystem;
	_GUIRenderer = GUIRenderer;

	_SoundManager = new SoundManager();
	_SoundManager->playStream("game", 0);

	_FPSWindow = CEGUI::WindowManager::getSingleton().getWindow("FPSWindow");
	_FPSUpdateFreq = 50;
	_FPSSkippedFrames = 0;

	_GameListener = new GameListener(snake);
	_MenuListener = new MenuListener();

    _Keyboard->setEventCallback(this);
    _Mouse->setEventCallback(this);

	_Continue = true;
	_Actif = 0;

	_Snake = snake;
}

EventListener::~EventListener()
{
	delete _SoundManager;
	delete _GameListener;
	delete _MenuListener;
}

bool EventListener::frameStarted(const Ogre::FrameEvent &evt)
{
	_Keyboard->capture();
	_Mouse->capture();

	switch(_Actif)
	{
		case 0:
			_GameListener->frameStarted(evt);
			break;
		case 1:
			_MenuListener->frameStarted(evt);
			break;
	}

	++_FPSSkippedFrames;
	if(_FPSSkippedFrames >= _FPSUpdateFreq)
	{
		_FPSSkippedFrames = 0;
		_FPSWindow->setText("FPS : " + Ogre::StringConverter::toString(_RenderWindow->getLastFPS()));
	}

	_SoundManager->update();

	return _Continue;
}

bool EventListener::keyPressed(const OIS::KeyEvent &e)
{
	switch(e.key)
	{
		case OIS::KC_SYSRQ:
			_RenderWindow->writeContentsToFile("screenshot_" + Ogre::StringConverter::toString((int)time(NULL)) + ".png");
			break;
	}

	switch(_Actif)
	{
		case 0:
			_Continue = _GameListener->keyPressed(e);
			break;
		case 1:
			_Continue = _MenuListener->keyPressed(e);
			break;
	}

    _GUISystem->injectKeyDown(e.key);
	_GUISystem->injectChar(e.text);

	return true;
}

bool EventListener::keyReleased(const OIS::KeyEvent &e)
{
	switch(_Actif)
	{
		case 0:
			_Continue = _GameListener->keyReleased(e);
			break;
		case 1:
			_Continue = _MenuListener->keyReleased(e);
			break;
	}

	_GUISystem->injectKeyUp(e.key);

    return true;
}

bool EventListener::mouseMoved(const OIS::MouseEvent &e)
{
	switch(_Actif)
	{
		case 0:
			_Continue = _GameListener->mouseMoved(e);
			break;
		case 1:
			_Continue = _MenuListener->mouseMoved(e);
			break;
	}

	_GUISystem->injectMouseMove(e.state.X.rel, e.state.Y.rel);
	_GUISystem->injectMouseWheelChange(e.state.Z.rel);

	return true;
}

bool EventListener::mousePressed(const OIS::MouseEvent &e, OIS::MouseButtonID id)
{
	switch(_Actif)
	{
		case 0:
			_Continue = _GameListener->mousePressed(e, id);
			break;
		case 1:
			_Continue = _MenuListener->mousePressed(e, id);
			break;
	}

	_GUISystem->injectMouseButtonDown(OISToCEGUI(id));

	return true;
}

bool EventListener::mouseReleased(const OIS::MouseEvent &e, OIS::MouseButtonID id)
{
	switch(_Actif)
	{
		case 0:
			_Continue = _GameListener->mouseReleased(e, id);
			break;
		case 1:
			_Continue = _MenuListener->mouseReleased(e, id);
			break;
	}

	_GUISystem->injectMouseButtonUp(OISToCEGUI(id));

	return true;
}

CEGUI::MouseButton EventListener::OISToCEGUI(int ois_button_id)
{
    switch (ois_button_id)
	{
		case 0: return CEGUI::LeftButton;
		case 1: return CEGUI::RightButton;
		case 2:	return CEGUI::MiddleButton;
		case 3: return CEGUI::X1Button;
		default: return CEGUI::NoButton;
	}
}

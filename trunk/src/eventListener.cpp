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

EventListener::EventListener(Ogre::SceneManager *sceneMgr, Ogre::RenderWindow *renderWindow, OIS::Keyboard *keyboard, OIS::Mouse *mouse, CEGUI::System *GUISystem, CEGUI::OgreCEGUIRenderer *GUIRenderer)
{
	_SceneManager = sceneMgr;
	_RenderWindow = renderWindow;

	_Keyboard = keyboard;
	_Mouse = mouse;

	_GUISystem = GUISystem;
	_GUIRenderer = GUIRenderer;

	_SoundManager = new SoundManager();
	_SoundManager->playStream("menu", rand() % _SoundManager->getNbTrack("menu"));

	Bonus *bonus = new Bonus(_SceneManager, _SceneManager->getRootSceneNode()->createChildSceneNode("Bonus_Node"));
	_Snake = new Snake(_SceneManager, _SceneManager->getRootSceneNode()->createChildSceneNode("Snake_HeadNode"), _SceneManager->getCamera("Camera"), bonus, _SoundManager);

	_GameListener = new GameListener(_Snake);
	_MenuListener = new MenuListener();

    _Keyboard->setEventCallback(this);
    _Mouse->setEventCallback(this);

	_Continue = true;
	_Actif = 1;

	_SceneManager->getCamera("Camera")->setPosition(-10000, 0, 0);
	_MenuLayout = CEGUI::WindowManager::getSingleton().loadWindowLayout((CEGUI::utf8*)"menu.layout");
	_GameLayout = CEGUI::WindowManager::getSingleton().loadWindowLayout((CEGUI::utf8*)"game.layout");
	_GUISystem->setGUISheet(_MenuLayout);
	CEGUI::ImagesetManager::getSingleton().createImagesetFromImageFile("image_fond", "fond.png");
	_MenuLayout->getChild("fond")->setProperty("Image", "set:image_fond image:full_image");
	CEGUI::PushButton *b = (CEGUI::PushButton *)_MenuLayout->getChild("fond")->getChild("quitter");
	b->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::SubscriberSlot(&EventListener::onQuit, this));
	b = (CEGUI::PushButton *)_MenuLayout->getChild("fond")->getChild("jouer");
	b->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::SubscriberSlot(&EventListener::onPlay, this));

	_GUISystem->setDefaultMouseCursor((CEGUI::utf8*)"TaharezLook", (CEGUI::utf8*)"MouseArrow");

	_FPSWindow = CEGUI::WindowManager::getSingleton().getWindow("FPSWindow");
	_FPSUpdateFreq = 50;
	_FPSSkippedFrames = 0;
	_TimerWindow = CEGUI::WindowManager::getSingleton().getWindow("StatsWindow");
	_Timer = new Ogre::Timer();
	_Time = 0;
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
			if(!_GameListener->frameStarted(evt))
				toMenu();
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

	if((int)(_Timer->getMilliseconds() / 1000) != _Time)
	{
		_Time = _Timer->getMilliseconds() / 1000;
		_TimerWindow->setText("Taille : " + Ogre::StringConverter::toString(_Snake->getSize()) + "\nTemps : " + Ogre::StringConverter::toString(_Time));
	}

	_SoundManager->update();

	return _Continue;
}

bool EventListener::keyPressed(const OIS::KeyEvent &e)
{
	switch(e.key)
	{
		case OIS::KC_SYSRQ:
			_SoundManager->playSound(2);
			_RenderWindow->writeContentsToFile("../Screenshots/User/screenshot_" + Ogre::StringConverter::toString((int)time(NULL)) + ".png");
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
	switch(e.key)
	{
		case OIS::KC_ESCAPE:
			if(!_Actif)
				toMenu();
			break;
	}

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

bool EventListener::onQuit(const CEGUI::EventArgs& e)
{
	_SoundManager->playSound(0);
	Sleep(200);
	_Continue = false;
	return true;
}

bool EventListener::onPlay(const CEGUI::EventArgs& e)
{
	_SoundManager->playSound(0);
	_GUISystem->setGUISheet(_GameLayout);
	_GUISystem->setDefaultMouseCursor(0);
	_SceneManager->getCamera("Camera")->setPosition(0, 0, 0);

	_Snake->reInit();
	_SoundManager->stopStream();
	_SoundManager->playStream("game", rand() % _SoundManager->getNbTrack("game"));

	_Actif = 0;

	_Timer->reset();
	_Time = 0;

	return true;
}

void EventListener::toMenu()
{
	_Snake->stop();
	_GameListener->stop();

	int taille = 0;
	int temps = 0;
	std::ifstream file;
	file.open("data.p3d", std::fstream::binary | std::fstream::in);
	if(file.is_open())
	{
		file.read((char *)(&taille), sizeof(int));
		file.read((char *)(&temps), sizeof(int));
		file.close();
	}

	if(_Snake->getSize() > taille)
	{
		Sleep(400);
		_SoundManager->playSound(7);
		Sleep(400);
		_SoundManager->playSound(7);
		Sleep(400);
		_SoundManager->playSound(7);
		Sleep(800);

		taille = _Snake->getSize();
		temps = _Time;
		std::ofstream file;
		file.open("data.p3d", std::fstream::binary | std::fstream::out | std::fstream::trunc);
		file.write((char *)(&taille), sizeof(int));
		file.write((char *)(&temps), sizeof(int));
		file.close();
		_SoundManager->playSound(2);
		_RenderWindow->writeContentsToFile("../Screenshots/HighScores/highscore.png");
		Sleep(800);
	}

	_SoundManager->stopStream();
	_SoundManager->playStream("menu", rand() % _SoundManager->getNbTrack("menu"));

	_GUISystem->setGUISheet(_MenuLayout);
	_GUISystem->setDefaultMouseCursor((CEGUI::utf8*)"TaharezLook", (CEGUI::utf8*)"MouseArrow");

	_Actif = 1;
}

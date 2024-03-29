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

    _Keyboard->setEventCallback(this);
    _Mouse->setEventCallback(this);

	_Continue = true;
	_FromMenu = true;
	_Actif = 1;

	_SceneManager->getCamera("Camera")->setPosition(-10000, 0, 0);
	_MenuLayout = CEGUI::WindowManager::getSingleton().loadWindowLayout((CEGUI::utf8*)"menu.layout");
	_MenuSpeedLayout = CEGUI::WindowManager::getSingleton().loadWindowLayout((CEGUI::utf8*)"menuspeed.layout");
	_GameLayout = CEGUI::WindowManager::getSingleton().loadWindowLayout((CEGUI::utf8*)"game.layout");
	_GameOverLayout = CEGUI::WindowManager::getSingleton().loadWindowLayout((CEGUI::utf8*)"gameover.layout");

	_GUISystem->setGUISheet(_MenuLayout);
	CEGUI::ImagesetManager::getSingleton().createImagesetFromImageFile("image_fond", "fond.png");
	_MenuLayout->getChild("fond")->setProperty("Image", "set:image_fond image:full_image");
	_MenuSpeedLayout->getChild("fond2")->setProperty("Image", "set:image_fond image:full_image");
	CEGUI::PushButton *b = (CEGUI::PushButton *)_MenuLayout->getChild("fond")->getChild("quitter");
	b->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::SubscriberSlot(&EventListener::onQuit, this));
	b = (CEGUI::PushButton *)_MenuLayout->getChild("fond")->getChild("jouer");
	b->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::SubscriberSlot(&EventListener::toSpeed, this));
	b = (CEGUI::PushButton *)_MenuLayout->getChild("fond")->getChild("clear");
	b->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::SubscriberSlot(&EventListener::onClear, this));

	b = (CEGUI::PushButton *)_MenuSpeedLayout->getChild("fond2")->getChild("normale");
	b->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::SubscriberSlot(&EventListener::toNormalSpeed, this));
	b = (CEGUI::PushButton *)_MenuSpeedLayout->getChild("fond2")->getChild("rapide");
	b->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::SubscriberSlot(&EventListener::toHighSpeed, this));
	b = (CEGUI::PushButton *)_MenuSpeedLayout->getChild("fond2")->getChild("insane");
	b->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::SubscriberSlot(&EventListener::toInsaneSpeed, this));

	_GUISystem->setDefaultMouseCursor((CEGUI::utf8*)"TaharezLook", (CEGUI::utf8*)"MouseArrow");

	b = (CEGUI::PushButton *)_GameOverLayout->getChild("Rejouer");
	b->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::SubscriberSlot(&EventListener::onPlay, this));
	b = (CEGUI::PushButton *)_GameOverLayout->getChild("Retour_au_menu");
	b->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::SubscriberSlot(&EventListener::toMenu, this));

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
}

bool EventListener::frameStarted(const Ogre::FrameEvent &evt)
{
	_Keyboard->capture();
	_Mouse->capture();

	if(!_Actif)
		if(!_GameListener->frameStarted(evt))
				gameOver();

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
			_SoundManager->playSound(1);
			_RenderWindow->writeContentsToFile("../Screenshots/User/screenshot_" + Ogre::StringConverter::toString((int)time(NULL)) + ".png");
			break;
	}

	if(!_Actif)
		_Continue = _GameListener->keyPressed(e);

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

	if(!_Actif)
		_Continue = _GameListener->keyReleased(e);


	_GUISystem->injectKeyUp(e.key);

    return true;
}

bool EventListener::mouseMoved(const OIS::MouseEvent &e)
{
	if(!_Actif)
		_Continue = _GameListener->mouseMoved(e);

	_GUISystem->injectMouseMove(e.state.X.rel, e.state.Y.rel);
	_GUISystem->injectMouseWheelChange(e.state.Z.rel);

	return true;
}

bool EventListener::mousePressed(const OIS::MouseEvent &e, OIS::MouseButtonID id)
{
	if(!_Actif)
		_Continue = _GameListener->mousePressed(e, id);

	_GUISystem->injectMouseButtonDown(OISToCEGUI(id));

	return true;
}

bool EventListener::mouseReleased(const OIS::MouseEvent &e, OIS::MouseButtonID id)
{
	if(!_Actif)
		_Continue = _GameListener->mouseReleased(e, id);

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
	onPlay();
	return true;
}

void EventListener::onPlay()
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
}

bool EventListener::toMenu(const CEGUI::EventArgs& e)
{
	_SoundManager->playSound(0);
	toMenu();
	return true;
}

void EventListener::toMenu()
{
	_Snake->stop();
	_GameListener->stop();

	_SoundManager->stopStream();
	_SoundManager->playStream("menu", rand() % _SoundManager->getNbTrack("menu"));

	_GUISystem->setGUISheet(_MenuLayout);
	_GUISystem->setDefaultMouseCursor((CEGUI::utf8*)"TaharezLook", (CEGUI::utf8*)"MouseArrow");

	_Actif = 1;
}

bool EventListener::toSpeed(const CEGUI::EventArgs& e)
{
	_SoundManager->playSound(0);
	_GUISystem->setGUISheet(_MenuSpeedLayout);
	return true;
}

void EventListener::gameOver()
{
	_Snake->stop();
	_GameListener->stop();

	_GUISystem->setGUISheet(_GameOverLayout);
	CEGUI::WindowManager::getSingleton().getWindow("StatsWindowGO")->setText(_TimerWindow->getText());
	_GUISystem->setDefaultMouseCursor((CEGUI::utf8*)"TaharezLook", (CEGUI::utf8*)"MouseArrow");

	int taille[3] = {0};
	int temps[3] = {0};

	std::ifstream file;
	file.open("data.p3d", std::fstream::binary | std::fstream::in);
	if(file.is_open())
	{
		for(int i = 0; i < 3; ++i)
		{
			file.read((char *)(&taille[i]), sizeof(int));
			file.read((char *)(&temps[i]), sizeof(int));
		}

		file.close();
	}

	CEGUI::WindowManager::getSingleton().getWindow("GameOver")->setText("       Game Over");

	int d;
	if(_Snake->getSpeed() == 100)
		d = 0;
	else if(_Snake->getSpeed() == 200)
		d = 1;
	else
		d = 2;

	if(_Snake->getSize() > taille[d])
	{
		_SoundManager->playSound(8);

		CEGUI::WindowManager::getSingleton().getWindow("GameOver")->setText("       Game Over\n Nouveau record !");

		taille[d] = _Snake->getSize();
		temps[d] = _Time;
		std::ofstream file;
		file.open("data.p3d", std::fstream::binary | std::fstream::out | std::fstream::trunc);

		for(int i = 0; i < 3; ++i)
		{
			file.write((char *)(&taille[i]), sizeof(int));
			file.write((char *)(&temps[i]), sizeof(int));
		}

		file.close();

		if(d == 0)
			_RenderWindow->writeContentsToFile("../Screenshots/HighScores/highscore_normal.png");
		else if(d == 1)
			_RenderWindow->writeContentsToFile("../Screenshots/HighScores/highscore_rapide.png");
		else
			_RenderWindow->writeContentsToFile("../Screenshots/HighScores/highscore_insane.png");
	}

	_SoundManager->playStream("menu", rand() % _SoundManager->getNbTrack("menu"));

	_Actif = 1;
}

bool EventListener::toNormalSpeed(const CEGUI::EventArgs &e)
{
	_Snake->setSpeed(100);
	onPlay();
	return true;
}

bool EventListener::toHighSpeed(const CEGUI::EventArgs &e)
{
	_Snake->setSpeed(200);
	onPlay();
	return true;
}

bool EventListener::toInsaneSpeed(const CEGUI::EventArgs &e)
{
	_Snake->setSpeed(400);
	onPlay();
	return true;
}

bool EventListener::onClear(const CEGUI::EventArgs &e)
{
	std::ofstream file;

	file.open("data.p3d", std::fstream::binary | std::fstream::out | std::fstream::trunc);
	file.close();

	return true;
}

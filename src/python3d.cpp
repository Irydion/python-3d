/*
-------------------------------------------------------------------------------
This file is part of Python3D.

Copyright (c) 2009 Emilien Dupont
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

#include "python3d.h"

Python3D::Python3D()
{
	_Root = 0;
	_SceneManager = 0;
	_RenderWindow = 0;
	_Viewport = 0;
	_Camera = 0;

	_InputManager = 0;
	_Keyboard = 0;
	_Mouse = 0;

	_GUISystem = 0;
	_GUIRenderer = 0;
}

Python3D::~Python3D()
{
	exit();
}

void Python3D::run()
{
 	_Root->startRendering();
}

void Python3D::start()
{
	_Root = new Ogre::Root();
	_Root->showConfigDialog();

	loadResources();

	_RenderWindow = _Root->initialise(true,"Python3D  -   By #undefined team");
	_SceneManager = _Root->createSceneManager(Ogre::ST_INTERIOR, "MainSceneManager");

	_Camera = _SceneManager->createCamera("Camera");
	_Camera->setNearClipDistance(1);
	_Camera->setFarClipDistance(2000);
	_Viewport = _RenderWindow->addViewport(_Camera);

	_SceneManager->setAmbientLight(Ogre::ColourValue(200, 200, 200));

	Ogre::Entity *entity = _SceneManager->createEntity("Map", "test.mesh");
	entity->setMaterialName("test");
	Ogre::SceneNode *node = _SceneManager->getRootSceneNode()->createChildSceneNode("MapNode");
	node->attachObject(entity);
	node->setScale(Ogre::Vector3(10, 10, 10));

	initOIS();
	initCEGUI();

	createFrameListener();
}

void Python3D::exit()
{
	delete _Listener;

	delete _GUISystem;
	delete _GUIRenderer;

	delete _Root;
}

void Python3D::loadResources()
{
	Ogre::ResourceGroupManager::getSingleton().addResourceLocation("../media/","FileSystem","General");
	Ogre::ResourceGroupManager::getSingleton().addResourceLocation("../media/gui/","FileSystem","General");
	Ogre::ResourceGroupManager::getSingleton().addResourceLocation("../media/models/","FileSystem","General");
	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
}

void Python3D::createFrameListener()
{
	_Listener = new EventListener(_SceneManager, _RenderWindow, _Keyboard, _Mouse, _GUISystem, _GUIRenderer);
	_Root->addFrameListener(_Listener);
}

void Python3D::initOIS()
{
	size_t windowHnd = 0;
    std::ostringstream windowHndStr;
    OIS::ParamList pl;
	Ogre::RenderWindow *win = _Root->getAutoCreatedWindow();

    win->getCustomAttribute("WINDOW", &windowHnd);
    windowHndStr << windowHnd;
    pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));
    _InputManager = OIS::InputManager::createInputSystem(pl);

    _Keyboard = static_cast<OIS::Keyboard*>(_InputManager->createInputObject(OIS::OISKeyboard, true));
    _Mouse = static_cast<OIS::Mouse*>(_InputManager->createInputObject(OIS::OISMouse, true));
}

void Python3D::initCEGUI()
{
	_GUIRenderer = new CEGUI::OgreCEGUIRenderer(_RenderWindow, Ogre::RENDER_QUEUE_OVERLAY, false, 3000, _SceneManager);
	_GUISystem = new CEGUI::System(_GUIRenderer, 0, 0, 0, (CEGUI::utf8*)"cegui.config");

	CEGUI::Logger::getSingleton().setLoggingLevel(CEGUI::Insane);
	CEGUI::Logger::getSingleton().setLogFilename("cegui.log");

	//_GUISystem->setDefaultMouseCursor((CEGUI::utf8*)"TaharezLook", (CEGUI::utf8*)"MouseArrow");
}

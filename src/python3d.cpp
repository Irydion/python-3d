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
	delete _Listener;

	delete _GUISystem;
	delete _GUIRenderer;

	delete _Root;
}

void Python3D::run()
{
 	_Root->startRendering();
}

void Python3D::start()
{
	_Root = new Ogre::Root();
	if(!_Root->restoreConfig() && !_Root->showConfigDialog())
		std::exit(0);

	loadResources();

	_RenderWindow = _Root->initialise(true,"Python3D  -   By #undefined team");
	_SceneManager = _Root->createSceneManager(Ogre::ST_INTERIOR, "MainSceneManager");

	_Camera = _SceneManager->createCamera("Camera");
	_Camera2 = _SceneManager->createCamera("Camera2");
	_Camera->setNearClipDistance(1);
	_Camera2->setNearClipDistance(1);

	if (_Root->getRenderSystem()->getCapabilities()->hasCapability(Ogre::RSC_INFINITE_FAR_PLANE))
	{
        _Camera->setFarClipDistance(0);
		_Camera2->setFarClipDistance(0);
	}
	else
	{
		_Camera->setFarClipDistance(5000);
		_Camera2->setFarClipDistance(0);
	}

	_Viewport = _RenderWindow->addViewport(_Camera);

	_SceneManager->setAmbientLight(Ogre::ColourValue(255, 255, 255));

	Ogre::Entity *map = _SceneManager->createEntity("Map", "map2.mesh");
	map->setQueryFlags(MAP_QUERY_FLAG);
	Ogre::SceneNode *node = _SceneManager->getRootSceneNode()->createChildSceneNode("General_MapNode");
	node->attachObject(map);
	node->setScale(Ogre::Vector3(10, 10, 10));

	initOIS();
	initCEGUI();

	Ogre::WindowEventUtilities::addWindowEventListener(_RenderWindow, new WinListener());

	createFrameListener();
}

void Python3D::exit()
{
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
	_GUISystem = new CEGUI::System(_GUIRenderer);
	CEGUI::SchemeManager::getSingleton().loadScheme((CEGUI::utf8*)"TaharezLookSkin.scheme");
	CEGUI::FontManager::getSingleton().createFont( "soloBig.font" );
	_GUISystem->setDefaultFont((CEGUI::utf8*)"solo");

	CEGUI::Logger::getSingleton().setLoggingLevel(CEGUI::Insane);
	CEGUI::Logger::getSingleton().setLogFilename("cegui.log");
}

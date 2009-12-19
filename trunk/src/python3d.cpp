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
	_Root = NULL;
	_SceneManager = NULL;
	_RenderWindow = NULL;
	_Viewport = NULL;
	_Camera = NULL;

	_InputManager = NULL;
	_Keyboard = NULL;
	_Mouse = NULL;
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
	_SceneManager = _Root->createSceneManager("BspSceneManager");

	_Camera = _SceneManager->createCamera("Camera");
	_Viewport = _RenderWindow->addViewport(_Camera);

	initOIS();
	createFrameListener();
}

void Python3D::exit()
{
	delete _Camera;
	delete _Viewport;
	delete _SceneManager;
	delete _RenderWindow;
	delete _Root;
}

void Python3D::loadResources()
{
	Ogre::ResourceGroupManager::getSingleton().addResourceLocation("../media/","FileSystem","General");
	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
}

void Python3D::createFrameListener()
{
	EventListener *listener = new EventListener(_SceneManager, _Keyboard, _Mouse);
	_Root->addFrameListener(listener);
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

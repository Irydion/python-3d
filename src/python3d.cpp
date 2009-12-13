#include "python3d.h"

Python3D::Python3D()
{
	_Root = NULL;
	_SceneManager = NULL;
	_RenderWindow = NULL;
	_Viewport = NULL;
	_Camera = NULL;
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

	_RenderWindow = _Root->initialise(true,"Python3D  -   By #undefined team");
	_SceneManager = _Root->createSceneManager("BspSceneManager");

	_Camera = _SceneManager->createCamera("Camera");
	_Viewport = _RenderWindow->addViewport(_Camera);

	initOIS();
	createFrameListener();
}

void Python3D::exit()
{
	if (_Root!=0)
		delete _Root;
}	

void Python3D::setupResources()
{

}

void Python3D::loadResources()
{

}

void Python3D::createFrameListener()
{
	GameListener *listener = new GameListener(_SceneManager, _Keyboard, _Mouse);
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

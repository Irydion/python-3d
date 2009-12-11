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
	_SceneManager = _Root->createSceneManager(Ogre::ST_GENERIC, "SceneManager");

	_Camera = _SceneManager->createCamera("Camera");
	_Viewport = _RenderWindow->addViewport(_Camera);
}

void Python3D::exit()
{
	if (_Root!=0)
		delete _Root;
}	
#ifndef PYTHON3D_H
#define PYTHON3D_H

#include "ogre.h"
#include "gameListener.h"
#include <OIS/OIS.h>

class Python3D
{
	public :
		Python3D();
		~Python3D();
		
		void start();
		void run();
		void exit();
		
	protected :
		void setupResources();
		void loadResources();

		void createFrameListener();

		void initOIS();

	protected :
		Ogre::Root* _Root;
		Ogre::SceneManager* _SceneManager;
		Ogre::RenderWindow* _RenderWindow;
		Ogre::Viewport* _Viewport;
		Ogre::Camera* _Camera;

		OIS::InputManager *_InputManager;
		OIS::Keyboard *_Keyboard;
		OIS::Mouse *_Mouse;
};

#endif // PYTHON3D_H

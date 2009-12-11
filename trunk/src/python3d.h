#ifndef PYTHON3D_H
#define PYTHON3D_H

#include "ogre.h"

class Python3D
{
	public :
		Python3D();
		~Python3D();
		
		void start();
		void run();
		void exit();
		
	public :
		Ogre::Root* _Root;
		Ogre::SceneManager* _SceneManager;
		Ogre::RenderWindow* _RenderWindow;
		Ogre::Viewport* _Viewport;
		Ogre::Camera* _Camera;
};

#endif // PYTHON3D_H
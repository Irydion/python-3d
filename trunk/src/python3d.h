/**
 * \file python3d.h
 * \brief Python3D : le jeu lui même
 * \author Emilien Dupont
 */

#ifndef PYTHON3D_H
#define PYTHON3D_H

#include "ogre.h"
#include <OIS/OIS.h>

#include "eventListener.h"

/*! \class Python3D
 * \brief classe principale du jeu
 *
 *  Cette classe s'occupe d'initialiser les librairies tierces et de charger les ressources avant de lancer le jeu.
 */
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

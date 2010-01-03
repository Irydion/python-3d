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

/**
 * \file python3d.h
 * \brief Python3D : le jeu lui m�me
 * \author Emilien Dupont
 */

#ifndef PYTHON3D_H
#define PYTHON3D_H

#include <ogre.h>
#include <OIS/OIS.h>
#include <CEGUI/CEGUI.h>
#include <OgreCEGUIRenderer.h>

#include "eventListener.h"
#include "snake.h"
#include "bonus.h"

/**
 * \class Python3D
 * \brief classe principale du jeu
 *
 *  Cette classe s'occupe d'initialiser les librairies tierces et de charger les ressources avant de lancer le jeu.
 */
class Python3D
{
	public :
		/**
		 * \brief Constructeur
		 *
		 * Constructeur de la classe Python3D
		 */
		Python3D();

		/**
		 * \brief Destructeur
		 *
		 * Destructeur de la classe Python3D
		 */
		~Python3D();
		
		/**
		 * \brief Initialisation
		 *
		 * M�thode qui initialise le jeu
		 */
		void start();
		/**
		 * \brief Lancement
		 *
		 * M�thode qui lance la boucle de rendu d'Ogre3D
		 */
		void run();
		/**
		 * \brief Arret
		 *
		 * M�thode qui lib�re la m�moire avant de quitter l'application
		 */
		void exit();
		
	protected :
		/**
		 * \brief Chargement des ressources
		 *
		 * M�thode qui charge toutes les ressources externes dont on a besoin
		 * 
		 * \remark
		 *		Les ressources sont charg�es dans le Resource Group Manager d'Ogre
		 */
		void loadResources();

		/**
		 * \brief Cr�ation du FrameListener
		 *
		 * M�thode qui cr�� puis ajoute le frame listener principal du jeu
		 *
		 */
		void createFrameListener();

		/**
		 * \brief Initialisation d'OIS
		 *
		 * M�thode qui initialise OIS et rattache la fen�tre du jeu � un InputManager
		 *
		 */
		void initOIS();

		/**
		 * \brief Initialisation de CEGUI
		 *
		 * M�thode qui initialise la librairie qui g�re l'interface utilisateur : CEGUI
		 *
		 */
		void initCEGUI();

	protected :
		/** Objet de base d'Ogre */
		Ogre::Root *_Root;
		/** Scene manager principal */
		Ogre::SceneManager *_SceneManager;
		/** La fenetre dans laquelle on fait le rendu */
		Ogre::RenderWindow *_RenderWindow;
		/** Viewport principal pour la cam�ra de jeu */
		Ogre::Viewport *_Viewport;
		/** Cam�ra du jeu */
		Ogre::Camera *_Camera;
		/** frame listener principal */
		EventListener *_Listener;

		/** InputManager d'OIS */
		OIS::InputManager *_InputManager;
		/** Clavier */
		OIS::Keyboard *_Keyboard;
		/** Souris */
		OIS::Mouse *_Mouse;

		/** Gestionnaire d'interface utilisateur CEGUI */
		CEGUI::OgreCEGUIRenderer *_GUIRenderer;
		/** objet syst�me CEGUI */
		CEGUI::System *_GUISystem;
};

#endif // PYTHON3D_H

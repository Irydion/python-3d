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
 * \file gameListener.h
 * \brief Le frame listener qui s'occupe de la gestion des événements "in-game"
 * \author Emilien Dupont
 */

#ifndef GAMELISTENER_H
#define GAMELISTENER_H

#include <ogre.h>
#include <OIS/OIS.h>

#include "snake.h"

/**
 * \class GameListener
 * \brief frame listener de jeu
 *
 *  Cette classe s'occupe de récupérer les entrées clavier/souris et de les traiter selon le déroulement actuel de la partie
 */
class GameListener
{
    public :
		/**
		 * \brief Constructeur
		 *
		 * Constructeur de la classe GameListener
		 */
		GameListener(Snake *snake);
		/**
		 * \brief Destructeur
		 *
		 * Destructeur de la classe GameListener
		 */
        ~GameListener();

		/**
		 * \brief Callback de début d'image
		 *
		 * Méthode appelée avant l'affichage de chaque image
		 *
		 * \param evt : informations sur l'image qui va être dessinée
		 * \return true pour continuer, false pour sortir de la boucle de rendu
		 */
		bool frameStarted(const Ogre::FrameEvent &evt);

		/**
		 * \brief Une touche est appuyée
		 *
		 * Méthode appelée lorsqu'une touche du clavier est appuyée
		 *
		 * \param e : informations sur la touche appuyée
		 * \return true pour continuer, false pour sortir de la boucle de rendu
		 */
		bool keyPressed(const OIS::KeyEvent &e);
		/**
		 * \brief Une touche est relachée
		 *
		 * Méthode appelée lorsqu'une touche du clavier est relachée
		 *
		 * \param e : informations sur la touche relachée
		 * \return true pour continuer, false pour sortir de la boucle de rendu
		 */
        bool keyReleased(const OIS::KeyEvent &e);

		/**
		 * \brief La souris a bougé
		 *
		 * Méthode appelée lorsque la souris a bougé
		 *
		 * \param e : informations sur le mouvement de la souris
		 * \return true pour continuer, false pour sortir de la boucle de rendu
		 */
        bool mouseMoved(const OIS::MouseEvent &e);
		/**
		 * \brief Un bouton de la souris est cliqué
		 *
		 * Méthode appelée lorsqu'un des boutons de la souris est appuyé
		 *
		 * \param e : informations sur la souris
		 * \param id : identifiant du bouton appuyé
		 * \return true pour continuer, false pour sortir de la boucle de rendu
		 */
        bool mousePressed(const OIS::MouseEvent &e, OIS::MouseButtonID id);
		/**
		 * \brief Un bouton de la souris est relaché
		 *
		 * Méthode appelée lorsqu'un des boutons de la souris est relaché
		 *
		 * \param e : informations sur la souris
		 * \param id : identifiant du bouton relaché
		 * \return true pour continuer, false pour sortir de la boucle de rendu
		 */
        bool mouseReleased(const OIS::MouseEvent &e, OIS::MouseButtonID id);

		/**
		 * \brief Méthode pour sortir du jeu
		 *
		 * Méthode à appeler pour revenir sur le menu (remet la caméra dans sa bonne position)
		 */
		void stop();

	protected :
		/** Caméra du jeu */
		Ogre::Camera *_Camera;

		/** True si le bouton droit de la souris est enfoncé, false sinon */
		bool _RightMouse;
		/** De combien de degrés on a tourné */
		Ogre::Real yaw;
		/** De combien de degrés on a tourné */
		Ogre::Real pitch;

		/** le serpent */
		Snake *_Snake;
};

#endif // GAMELISTENER_H

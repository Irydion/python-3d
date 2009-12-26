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

/**
 * \file snake.h
 * \brief Snake : le serpent
 * \author Emilien Dupont
 */

#ifndef SNAKE_H
#define SNAKE_H

#include <ogre.h>

/**
 * \class Snake
 * \brief le serpent
 *
 *  Cette classe g�re le serpent (position, taille, d�placement, etc.).
 */
class Snake
{
	public:
		/**
		 * \brief Constructeur
		 *
		 * Constructeur de la classe Snake.
		 *
		 * \param sceneMgr : un pointeur vers le scene manager principal du jeu
		 * \param head : node de la tete
		 * \param cam : camera qui doit etre rattach�e � la tete
		 * \param taille : taille initiale du serpent
		 */
		Snake(Ogre::SceneManager *sceneMgr, Ogre::SceneNode *head, Ogre::Camera *cam, unsigned int size);
		/**
		 * \brief Destructeur
		 *
		 * Destructeur de la classe Snake.
		 */
		~Snake();

		void turnUp();
		void turnDown();
		void turnRight();
		void turnLeft();

		/**
		 * \brief Mise � jour du serpent
		 *
		 * Met � jour la position du serpent.
		 *
		 * \remark m�thode � appeler une fois par image
		 */
		void update(Ogre::Real timeSinceLastFrame);

	public:
		/** Node de la t�te */
		Ogre::SceneNode *_Head;

	protected:
		/** Direction actuelle du serpent */
		Ogre::Vector3 _Direction;
		/** Taille */
		unsigned int _Size;
		/** 0 si le snake tourne pas ; 1:haut 2:bas 3:droite 4:gauche */
		int _IsTurning;
		/** Indique, si on est en train de tourner, � quel angle on en est */
		Ogre::Real _ActualAngle;
		/** Vitesse de rotation */
		Ogre::Real _TurnSpeed;

		/** Requ�te pour r�cup�rer les informations le long d'un rayon */
		Ogre::RaySceneQuery *_RayQuery;
		/** Rayon de d�tection de collision avec la tete */
		Ogre::Ray _Ray;
};

#endif // SNAKE_H

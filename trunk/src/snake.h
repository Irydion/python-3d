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

#include "CollisionTools.h"

/** le flag associ� � la map pour la d�tection de collision */
#define MAP_QUERY_FLAG 1<<0
/** le flag associ� aux bonus pour la d�tection de collision */
#define BONUS_QUERY_FLAG 1<<1

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
		 * \param size : taille initiale du serpent
		 */
		Snake(Ogre::SceneManager *sceneMgr, Ogre::SceneNode *head, Ogre::Camera *cam, unsigned int size);
		/**
		 * \brief Destructeur
		 *
		 * Destructeur de la classe Snake.
		 */
		~Snake();

		/**
		 * \brief Tourner vers le haut
		 *
		 * Demande au snake de tourner de 90� vers le haut en plusieurs images
		 */
		void turnUp();
		/**
		 * \brief Tourner vers le bas
		 *
		 * Demande au snake de tourner de 90� vers le bas en plusieurs images
		 */
		void turnDown();
		/**
		 * \brief Tourner vers la droite
		 *
		 * Demande au snake de tourner de 90� vers la droite en plusieurs images
		 */
		void turnRight();
		/**
		 * \brief Tourner vers la gauche
		 *
		 * Demande au snake de tourner de 90� vers la gauche en plusieurs images
		 */
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
		/** prochain mouvement � effectuer */
		int _NextTurn;

		/** outil de MOC pour d�tecter les collisions */
		MOC::CollisionTools *_CollisionTools;
		/** derniere position prise par la tete du snake */
		Ogre::Vector3 _LastPosition;
};

#endif // SNAKE_H
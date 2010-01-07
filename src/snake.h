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
 * \file snake.h
 * \brief Snake : le serpent
 * \author Emilien Dupont
 */

#ifndef SNAKE_H
#define SNAKE_H

#include <ogre.h>
#include <CollisionTools.h>

#include "bonus.h"
#include "SoundManager.h"

/**
 * \class Snake
 * \brief le serpent
 *
 *  Cette classe gère le serpent (position, taille, déplacement, etc.).
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
		 * \param cam : camera qui doit etre rattachée à la tete
		 * \param size : taille initiale du serpent
		 * \param b : un pointeur vers le bonus à prendre
		 */
		Snake(Ogre::SceneManager *sceneMgr, Ogre::SceneNode *head, Ogre::Camera *cam, Bonus *b, SoundManager *soundMgr);
		/**
		 * \brief Destructeur
		 *
		 * Destructeur de la classe Snake.
		 */
		~Snake();

		void reInit();
		void stop();

		/**
		 * \brief Tourner vers le haut
		 *
		 * Demande au snake de tourner de 90° vers le haut en plusieurs images
		 */
		void turnUp();
		/**
		 * \brief Tourner vers le bas
		 *
		 * Demande au snake de tourner de 90° vers le bas en plusieurs images
		 */
		void turnDown();
		/**
		 * \brief Tourner vers la droite
		 *
		 * Demande au snake de tourner de 90° vers la droite en plusieurs images
		 */
		void turnRight();
		/**
		 * \brief Tourner vers la gauche
		 *
		 * Demande au snake de tourner de 90° vers la gauche en plusieurs images
		 */
		void turnLeft();

		/**
		 * \brief Mise à jour du serpent
		 *
		 * Met à jour la position du serpent.
		 *
		 * \remark méthode à appeler une fois par image
		 */
		bool update(Ogre::Real timeSinceLastFrame);

	public:
		/** Node de la tête */
		Ogre::SceneNode *_Head;

	protected:
		/** Direction actuelle du serpent */
		Ogre::Vector3 _Direction;
		/** Taille */
		int _Size;
		/** 0 si le snake tourne pas ; 1:haut 2:bas 3:droite 4:gauche */
		int _IsTurning;
		/** Indique, si on est en train de tourner, à quel angle on en est */
		Ogre::Real _ActualAngle;
		/** Vitesse de rotation */
		Ogre::Real _TurnSpeed;
		/** Prochain mouvement à effectuer */
		int _NextTurn;
		/** Temps restant avant l'apparition de la prochaine entité pour la queue du serpent */
		Ogre::Real _NextEnt;
		/** Nombre de node actuels pour la queue du serpent */
		int _NbNode;
		/** L'ordre des nodes dans la queue du serpent */
		std::deque<int> _ListNode;
		/** Dernier node de la queue du serpent (celui à faire "disparaître" au prochain changement dans la deque) */
		Ogre::SceneNode *_TailNode;
		Ogre::SceneNode *_CompassNode;

		/** outil de MOC pour détecter les collisions */
		MOC::CollisionTools *_CollisionTools;
		/** derniere position prise par la tete du snake */
		Ogre::Vector3 _LastPosition;

		/** Bonus à attraper pour grandir */
		Bonus *_Bonus;
		/** Scene manager principal */
		Ogre::SceneManager *_SceneManager;
		SoundManager *_SoundManager;
};

#endif // SNAKE_H

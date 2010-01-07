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
 * \file bonus.h
 * \brief La classe bonus
 * \author Emilien Dupont
 */

#ifndef BONUS_H
#define BONUS_H

#include <ogre.h>
#include <CollisionTools.h>

/**
 * \class Bonus
 * \brief la classe qui gère le bonus
 *
 *  Cette classe s'occupe de gérer l'affichage et le positionnement du bonus
 */
class Bonus
{
	public:
		/**
		 * \brief Constructeur
		 *
		 * Constructeur de la classe bonus
		 *
		 * \param sceneMgr : un pointeur vers le scene manager principal du jeu
		 * \param node : un pointeur vers le scene node créée pour l'affichage du bonus
		 */
		Bonus(Ogre::SceneManager *sceneMgr, Ogre::SceneNode *node);
		/**
		 * \brief Destructeur
		 *
		 * Destructeur de la classe bonus
		 */
		~Bonus();

		/**
		 * \brief Repositionne le bonus
		 *
		 * Méthode qui calcul une nouvelle position pour le bonus une fois qu'il a été pris
		 */
		void changeBonus();

		Ogre::Vector3 getPosition();

	protected:
		/** L'entité du bonus */
		Ogre::Entity *_Entity;
		/** Le scene node auquel est rattaché le bonus */
		Ogre::SceneNode *_Node;

		/** outils de MOC pour détecter les collisions pour le repositionnement */
		MOC::CollisionTools *_CollisionTool;
};

#endif // BONUS_H

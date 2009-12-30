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
 * \file bonus.h
 * \brief La classe bonus
 * \author Emilien Dupont
 */

#ifndef BONUS_H
#define BONUS_H

#include <ogre.h>
#include <CollisionTools.h>

class Bonus
{
	public:
		Bonus(Ogre::SceneManager *sceneMgr, Ogre::SceneNode *node);
		~Bonus();

		void changeBonus();

	protected:
		Ogre::Entity *_Entity;
		Ogre::SceneNode *_Node;

		MOC::CollisionTools *_CollisionTool;
};

#endif // BONUS_H

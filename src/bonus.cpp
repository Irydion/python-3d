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

#include "bonus.h"

Bonus::Bonus(Ogre::SceneManager *sceneMgr, Ogre::SceneNode *node)
{
	_Entity = sceneMgr->createEntity("Bonus", "Sphere.mesh");
	_Entity->setQueryFlags(BONUS_QUERY_FLAG);

	_Node = node;
	_Node->attachObject(_Entity);
	_Node->setPosition(Ogre::Vector3(0, 400, 0));
	_Node->setScale(20, 20, 20);
}

Bonus::~Bonus()
{

}

void Bonus::changeBonus()
{
	_Node->setPosition(Ogre::Vector3(rand() % 300 + 50, rand() % 700 + 50, rand() % 300 + 50));
}

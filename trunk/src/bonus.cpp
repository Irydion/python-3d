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

#include "bonus.h"

Bonus::Bonus(Ogre::SceneManager *sceneMgr, Ogre::SceneNode *node)
{
	_Entity = sceneMgr->createEntity("Bonus", "Sphere.mesh");
	_Entity->setQueryFlags(BONUS_QUERY_FLAG);

	_Node = node;
	_Node->attachObject(_Entity);
	_Node->setPosition(Ogre::Vector3(0, 0, 0));
	_Node->setScale(20, 20, 20);

	_CollisionTool = new MOC::CollisionTools(sceneMgr);
}

Bonus::~Bonus()
{
	delete _CollisionTool;
}

void Bonus::changeBonus()
{
	int direction;
	Ogre::Vector3 next;
	Ogre::Vector3 pos;
	for(int i = 0; i < 60; ++i)
	{
		pos = _Node->getPosition();
		next = pos;
		direction = rand() % 6;
		switch(direction)
		{
			case 0:
				next.x += 20;
				break;
			case 1:
				next.y += 20;
				break;
			case 2:
				next.z += 20;
				break;
			case 3:
				next.x -= 20;
				break;
			case 4:
				next.y -= 20;
				break;
			case 5:
				next.z -= 20;
		}
		if(!_CollisionTool->collidesWithEntity(pos, next, 10, 0, MAP_QUERY_FLAG))
			_Node->setPosition(next);
	}
}

Ogre::Vector3 Bonus::getPosition()
{
	return _Node->getPosition();
}

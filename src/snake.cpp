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

#include "snake.h"

Snake::Snake(Ogre::SceneNode *head, Ogre::Camera *cam, unsigned int size)
{
	_Head = head;
	_Size = size;

	_Head->attachObject(cam);
	_Head->translate(Ogre::Vector3(0, 200, 0));
}

Snake::~Snake()
{

}

void Snake::update(Ogre::Real timeSinceLastFrame)
{
	_Head->translate(_Direction * timeSinceLastFrame, Ogre::Node::TS_LOCAL);
}

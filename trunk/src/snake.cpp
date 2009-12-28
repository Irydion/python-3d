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

Snake::Snake(Ogre::SceneManager *sceneMgr, Ogre::SceneNode *head, Ogre::Camera *cam, unsigned int size)
{
	_Head = head;
	_Size = size;
	_TurnSpeed = 0;
	_IsTurning = 0;
	_ActualAngle = 0;
	_NextTurn = 0;
	_LastPosition = Ogre::Vector3(0, 0, 0);

	_CollisionTools = new MOC::CollisionTools(sceneMgr);

	_Head->attachObject(cam);
	_Head->translate(Ogre::Vector3(0, 200, 0));

	_Direction = Ogre::Vector3(0, 0, -100);
}

Snake::~Snake()
{
	delete _CollisionTools;
}

void Snake::turnUp()
{
	if(!_IsTurning)
	{
		_IsTurning = 1;
		_TurnSpeed = 200;
	}
	else
	{
		_NextTurn = 1;
	}
}

void Snake::turnDown()
{
	if(!_IsTurning)
	{
		_IsTurning = 2;
		_TurnSpeed = -200;
	}
	else
	{
		_NextTurn = 2;
	}
}

void Snake::turnRight()
{
	if(!_IsTurning)
	{
		_IsTurning = 3;
		_TurnSpeed = -200;
	}
	else
	{
		_NextTurn = 3;
	}
}

void Snake::turnLeft()
{
	if(!_IsTurning)
	{
		_IsTurning = 4;
		_TurnSpeed = 200;
	}
	else
	{
		_NextTurn = 4;
	}
}

void Snake::update(Ogre::Real timeSinceLastFrame)
{
	_LastPosition = _Head->getPosition();
	_Head->translate(_Direction * timeSinceLastFrame, Ogre::Node::TS_LOCAL);

	if(_IsTurning)
	{
		_ActualAngle += _TurnSpeed * timeSinceLastFrame;

		if(_IsTurning < 3)
		{
			_Head->pitch(Ogre::Degree(_TurnSpeed * timeSinceLastFrame));
		}
		else
		{
			_Head->yaw(Ogre::Degree(_TurnSpeed * timeSinceLastFrame));
		}

		if(_ActualAngle >= 90 || _ActualAngle <= -90)
		{
			_ActualAngle = 0;
			_IsTurning = 0;
			switch(_NextTurn)
			{
				case 0:
					break;
				case 1:
					turnUp();
					break;
				case 2:
					turnDown();
					break;
				case 3:
					turnRight();
					break;
				case 4:
					turnLeft();
					break;
			}
			_NextTurn = 0;
		}
	}

	if(_CollisionTools->collidesWithEntity(_LastPosition, _Head->getPosition(), 10, 0, MAP_QUERY_FLAG))
	{
		// COLLISION MAP -> fin de partie
		_Head->setPosition(_LastPosition);
	}
	if(_CollisionTools->collidesWithEntity(_LastPosition, _Head->getPosition(), 10, 0, BONUS_QUERY_FLAG))
	{
		// COLLISION BONUS -> agrandir
	}
}
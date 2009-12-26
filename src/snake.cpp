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

	_Head->attachObject(cam);
	_Head->translate(Ogre::Vector3(0, 200, 0));

	_Direction = Ogre::Vector3(0, 0, -100);

	_RayQuery = sceneMgr->createRayQuery(Ogre::Ray(_Head->getPosition(), _Head->getOrientation().zAxis()));
	_RayQuery->setWorldFragmentType(Ogre::SceneQuery::WFT_SINGLE_INTERSECTION);
}

Snake::~Snake()
{

}

void Snake::turnUp()
{
	if(!_IsTurning)
	{
		_IsTurning = 1;
		_TurnSpeed = 200;
	}
}

void Snake::turnDown()
{
	if(!_IsTurning)
	{
		_IsTurning = 2;
		_TurnSpeed = -200;
	}
}

void Snake::turnRight()
{
	if(!_IsTurning)
	{
		_IsTurning = 3;
		_TurnSpeed = -200;
	}
}

void Snake::turnLeft()
{
	if(!_IsTurning)
	{
		_IsTurning = 4;
		_TurnSpeed = 200;
	}
}

void Snake::update(Ogre::Real timeSinceLastFrame)
{
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
		}
	}

	_Ray.setOrigin(_Head->getPosition());
    _Ray.setDirection(-(_Head->getOrientation().zAxis()));

	_RayQuery->setRay(_Ray);
	Ogre::RaySceneQueryResult &_QueryResult = _RayQuery->execute();
	Ogre::RaySceneQueryResult::iterator i = _QueryResult.begin();

    if (i != _QueryResult.end() && i->worldFragment)
    {
        if(i->distance < 35)
        {
			MessageBoxA(NULL, "Boom ! collision ...", "An exception has occurred!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
        }
    }
}

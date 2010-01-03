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

#include "snake.h"

Snake::Snake(Ogre::SceneManager *sceneMgr, Ogre::SceneNode *head, Ogre::Camera *cam, Bonus *b, SoundManager *soundMgr)
{
	_Head = head;
	_Size = 42;
	_TurnSpeed = 0;
	_IsTurning = 0;
	_ActualAngle = 0;
	_NextTurn = 0;
	_LastPosition = Ogre::Vector3(0, 0, 0);
	_Bonus = b;
	_NextEnt = 0;
	_NbNode = -1;

	_CollisionTools = new MOC::CollisionTools(sceneMgr);
	_SceneManager = sceneMgr;
	_SoundManager = soundMgr;

	_Head->attachObject(cam);
	_Head->setPosition(Ogre::Vector3(-400, 0, 0));

	_Direction = Ogre::Vector3(0, 0, -100);
}

Snake::~Snake()
{
	delete _CollisionTools;
}

void Snake::reInit()
{
	_Size = 42;
	_TurnSpeed = 0;
	_IsTurning = 0;
	_ActualAngle = 0;
	_NextTurn = 0;
	_LastPosition = Ogre::Vector3(0, 0, 0);
	_NextEnt = 0;
	_NbNode = -1;
	_ListNode.empty();

	_SceneManager->getCamera("Camera")->setPosition(0, 0, 0);
	_Head->setPosition(Ogre::Vector3(-400, 0, 0));
	_Head->setOrientation(Ogre::Quaternion::IDENTITY);

	_Direction = Ogre::Vector3(0, 0, -100);

	_SoundManager->playSound(3);
	Sleep(1000);
}

void Snake::stop()
{
	Ogre::SceneNode *n;
	while(_ListNode.size() > 0)
	{
		n = _SceneManager->getSceneNode("snakeNode" + Ogre::StringConverter::toString(_ListNode.front()));
		n->detachAllObjects();
		_ListNode.pop_front();
	}
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

bool Snake::update(Ogre::Real timeSinceLastFrame)
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

	if(_NextEnt <= 0)
	{
		_NextEnt = 0.25;
		if(_NbNode < _Size)
		{
			++_NbNode;

			Ogre::Entity *ent;
			if(_SceneManager->hasEntity("snakeEnt" + Ogre::StringConverter::toString(_NbNode)))
			{
				ent = _SceneManager->getEntity("snakeEnt" + Ogre::StringConverter::toString(_NbNode));
			}
			else
			{
				ent = _SceneManager->createEntity("snakeEnt" + Ogre::StringConverter::toString(_NbNode), "snake.mesh");
			}
			ent->setQueryFlags(SNAKE_QUERY_FLAG);

			if(_SceneManager->hasSceneNode("snakeNode" + Ogre::StringConverter::toString(_NbNode)))
			{
				_TailNode = _SceneManager->getSceneNode("snakeNode" + Ogre::StringConverter::toString(_NbNode));
			}
			else
			{
				_TailNode = _SceneManager->getRootSceneNode()->createChildSceneNode("snakeNode" + Ogre::StringConverter::toString(_NbNode));
			}
			_TailNode->attachObject(ent);
			_TailNode->setPosition(_LastPosition);
			_TailNode->setScale(10, 10, 10);

			_ListNode.push_back(_NbNode);
			_TailNode = _SceneManager->getSceneNode("snakeNode" + Ogre::StringConverter::toString(_ListNode.front()));
		}
		else
		{
			_TailNode = _SceneManager->getSceneNode("snakeNode" + Ogre::StringConverter::toString(_ListNode.front()));
			_TailNode->setPosition(_LastPosition);
			_TailNode->setScale(10, 10, 10);

			_ListNode.push_back(_ListNode.front());
			_ListNode.pop_front();
			_TailNode = _SceneManager->getSceneNode("snakeNode" + Ogre::StringConverter::toString(_ListNode.front()));
		}
	}
	else if(_NbNode == _Size)
	{
		_TailNode->setScale(_TailNode->getScale().x - 40 * timeSinceLastFrame, _TailNode->getScale().y - 40 * timeSinceLastFrame, _TailNode->getScale().z - 40 * timeSinceLastFrame);
	}
	_NextEnt -= timeSinceLastFrame;

	if(_CollisionTools->collidesWithEntity(_LastPosition, _Head->getPosition(), 15, 0, MAP_QUERY_FLAG | SNAKE_QUERY_FLAG))
	{
		_SoundManager->playSound(5);
		Sleep(800);
		_SoundManager->playSound(4);
		Sleep(1000);
		return false;
	}
	if(_CollisionTools->collidesWithEntity(_LastPosition, _Head->getPosition(), 20, 0, BONUS_QUERY_FLAG))
	{
		_Size += _Size/5;
		_Bonus->changeBonus();
		_SoundManager->playSound(rand() % 3 + 6);
	}

	return true;
}

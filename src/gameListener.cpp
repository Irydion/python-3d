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

#include "gameListener.h"

GameListener::GameListener(Snake *snake)
{
	_Snake = snake;
	_Camera = (Ogre::Camera *)(_Snake->_Head->getAttachedObject("Camera"));

	_RightMouse = false;
}

GameListener::~GameListener()
{
}

bool GameListener::frameStarted(const Ogre::FrameEvent &evt)
{
	_Snake->update(evt.timeSinceLastFrame);
	return true;
}

bool GameListener::keyPressed(const OIS::KeyEvent &e)
{
	switch(e.key)
	{
		case OIS::KC_UP:
		case OIS::KC_W:
			_Snake->turnUp();
			break;
		case OIS::KC_DOWN:
		case OIS::KC_S:
			_Snake->turnDown();
			break;
		case OIS::KC_RIGHT:
		case OIS::KC_D:
			_Snake->turnRight();
			break;
		case OIS::KC_LEFT:
		case OIS::KC_A:
			_Snake->turnLeft();
			break;
	}
	return true;
}

bool GameListener::keyReleased(const OIS::KeyEvent &e)
{
	switch (e.key)
    {
        case OIS::KC_ESCAPE:
            return false;
            break;
    }

    return true;
}

bool GameListener::mouseMoved(const OIS::MouseEvent &e)
{
	if(_RightMouse)
	{
		_Camera->yaw(Ogre::Degree(e.state.X.rel * -0.1));
		_Camera->pitch(Ogre::Degree(e.state.Y.rel * -0.1));
		yaw += e.state.X.rel * 0.1;
		pitch += e.state.Y.rel * 0.1;
	}

	return true;
}

bool GameListener::mousePressed(const OIS::MouseEvent &e, OIS::MouseButtonID id)
{
	if(id == OIS::MB_Right)
    {
        _RightMouse = true;
		yaw = 0;
		pitch = 0;
    }

	return true;
}

bool GameListener::mouseReleased(const OIS::MouseEvent &e, OIS::MouseButtonID id)
{
	if(id == OIS::MB_Right)
    {
        _RightMouse = false;
		_Camera->yaw(Ogre::Degree(yaw));
		_Camera->pitch(Ogre::Degree(pitch));
    }

	return true;
}
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

#include "menuListener.h"

MenuListener::MenuListener()
{
}

MenuListener::~MenuListener()
{
}

bool MenuListener::frameStarted(const Ogre::FrameEvent &evt)
{
	return true;
}

bool MenuListener::keyPressed(const OIS::KeyEvent &e)
{
	return true;
}

bool MenuListener::keyReleased(const OIS::KeyEvent &e)
{
    return true;
}

bool MenuListener::mouseMoved(const OIS::MouseEvent &e)
{
	return true;
}

bool MenuListener::mousePressed(const OIS::MouseEvent &e, OIS::MouseButtonID id)
{
	return true;
}

bool MenuListener::mouseReleased(const OIS::MouseEvent &e, OIS::MouseButtonID id)
{
	return true;
}

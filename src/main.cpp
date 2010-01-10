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
 * \file main.cpp
 * \brief Python3D, un jeu du snake dans un espace en 3 dimensions.
 * \author Emilien Dupont
 *
 * Python3D est le principe du jeu du serpent adapté sur une "grille" en 3 dimensions, le "snake" peut ainsi se déplacer
 * vers, le haut et le bas en plus des directions habituelles.
 */

#include "windows.h"
#include "ogre.h"
#include "python3d.h"

using namespace std;

/**
 * \fn INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT)
 * \brief Entrée du programme.
 *
 * \return EXIT_SUCCESS - Arrêt normal du programme.
 */
INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT )
{
	srand(time(0));

    try
	{
		Python3D *game = new Python3D();
		game->start();
		game->run();
		delete game;
    }	
	catch(Ogre::Exception &e)
	{
        MessageBoxA( NULL, e.what(), "An exception has occurred!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
    }
	catch(const exception &e)
	{
		MessageBoxA( NULL, e.what(), "An exception has occurred!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
	}
	catch(...)
	{
		MessageBoxA( NULL, "Unknown exception !", "An exception has occurred!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
	}

    return EXIT_SUCCESS;
}

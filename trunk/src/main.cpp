/**
 * \file main.cpp
 * \brief Python3D, un jeu du snake dans un espace en 3 dimensions.
 * \author Emilien Dupont
 *
 * Python3D est le principe du jeu du serpent adapt� sur une "grille" en 3 dimensions, le "snake" peut ainsi se d�placer
 * vers, le haut et le bas en plus des directions habituelles.
 */

#include "windows.h"
#include "ogre.h"
#include "python3d.h"

using namespace std;

/**
 * \fn INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT)
 * \brief Entr�e du programme.
 *
 * \return EXIT_SUCCESS - Arr�t normal du programme.
 */
INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT )
{
    try
	{
		Python3D game;
		game.start();
		game.run();
		game.exit();
    }	
	catch( Ogre::Exception &e )
	{
        MessageBoxA( NULL, e.what(), "An exception has occurred!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
    }

    return EXIT_SUCCESS;
}

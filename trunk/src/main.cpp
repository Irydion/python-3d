#include <cstdlib>

#include "windows.h"
#include "ogre.h"
#include "python3d.h"

using namespace std;

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

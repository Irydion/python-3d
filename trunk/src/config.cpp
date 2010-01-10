#include "windows.h"
#include "ogre.h"

using namespace std;

INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT )
{
    try
	{
		Ogre::Root *root = new Ogre::Root();
		root->showConfigDialog();
		delete root;
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
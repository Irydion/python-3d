#ifndef GAMELISTENER_H
#define GAMELISTENER_H

#include "ogre.h"
#include <OIS/OIS.h>

class GameListener
{
    public:
		GameListener();
        ~GameListener();

		bool frameStarted(const Ogre::FrameEvent &evt);

		bool keyPressed(const OIS::KeyEvent &e);
        bool keyReleased(const OIS::KeyEvent &e);

        bool mouseMoved(const OIS::MouseEvent &e);
        bool mousePressed(const OIS::MouseEvent &e, OIS::MouseButtonID id);
        bool mouseReleased(const OIS::MouseEvent &e, OIS::MouseButtonID id);
};

#endif // GAMELISTENER_H

#ifndef MENULISTENER_H
#define MENULISTENER_H

#include "ogre.h"
#include <OIS/OIS.h>

class MenuListener
{
    public:
		MenuListener();
        ~MenuListener();

		bool frameStarted(const Ogre::FrameEvent &evt);

		bool keyPressed(const OIS::KeyEvent &e);
        bool keyReleased(const OIS::KeyEvent &e);

        bool mouseMoved(const OIS::MouseEvent &e);
        bool mousePressed(const OIS::MouseEvent &e, OIS::MouseButtonID id);
        bool mouseReleased(const OIS::MouseEvent &e, OIS::MouseButtonID id);
};

#endif // MENULISTENER_H

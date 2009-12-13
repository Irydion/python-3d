#ifndef EVENTLISTENER_H
#define EVENTLISTENER_H

#include "ogre.h"
#include <OIS/OIS.h>

#include "gameListener.h"
#include "menuListener.h"

class EventListener : public Ogre::FrameListener, public OIS::KeyListener, public OIS::MouseListener
{
	public:
		EventListener(Ogre::SceneManager *sceneMgr, OIS::Keyboard *keyboard, OIS::Mouse *mouse);
        ~EventListener();

		bool frameStarted(const Ogre::FrameEvent &evt);

		bool keyPressed(const OIS::KeyEvent &e);
        bool keyReleased(const OIS::KeyEvent &e);

        bool mouseMoved(const OIS::MouseEvent &e);
        bool mousePressed(const OIS::MouseEvent &e, OIS::MouseButtonID id);
        bool mouseReleased(const OIS::MouseEvent &e, OIS::MouseButtonID id);

	protected:
		Ogre::SceneManager *_SceneManager;

		OIS::Keyboard *_Keyboard;
		OIS::Mouse *_Mouse;

		bool _Continue;

		int _Actif;
		GameListener *gameListener;
		MenuListener *menuListener;
};

#endif // EVENTLISTENER_H

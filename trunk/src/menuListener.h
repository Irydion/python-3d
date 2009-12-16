/**
 * \file menuListener.h
 * \brief Le frame listener qui s'occupe de la gestion des événements dans le menu
 * \author Emilien Dupont
 */

#ifndef MENULISTENER_H
#define MENULISTENER_H

#include "ogre.h"
#include <OIS/OIS.h>

/*! \class MenuListener
 * \brief frame listener du menu
 *
 *  Cette classe s'occupe de récupérer les entrées clavier/souris et de les traiter dans le menu
 */
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

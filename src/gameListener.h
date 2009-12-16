/**
 * \file gameListener.h
 * \brief Le frame listener qui s'occupe de la gestion des �v�nements "in-game"
 * \author Emilien Dupont
 */

#ifndef GAMELISTENER_H
#define GAMELISTENER_H

#include "ogre.h"
#include <OIS/OIS.h>

/*! \class GameListener
 * \brief frame listener de jeu
 *
 *  Cette classe s'occupe de r�cup�rer les entr�es clavier/souris et de les traiter selon le d�roulement actuel de la partie
 */
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

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
 * \file eventListener.h
 * \brief Le frame listener principal qui contient les sous-listeners et s'occupe de relier les informations vers eux
 * \author Emilien Dupont
 */

#ifndef EVENTLISTENER_H
#define EVENTLISTENER_H

#include <ogre.h>
#include <OIS/OIS.h>
#include <CEGUI/CEGUI.h>
#include <OgreCEGUIRenderer.h>

#include "gameListener.h"
#include "menuListener.h"
#include "soundManager.h"
#include "snake.h"

/**
 * \class EventListener
 * \brief frame listener principal
 *
 *  Cette classe s'occupe de r�cup�rer les entr�es clavier/souris et de les transferer au frame listener actif � chaque frame.
 */
class EventListener : public Ogre::FrameListener, public OIS::KeyListener, public OIS::MouseListener
{
	public :
		/**
		 * \brief Constructeur
		 *
		 * Constructeur de la classe EventListener
		 *
		 * \param sceneMgr : un pointeur vers le scene manager principal du jeu
		 * \param renderWindow : fenetre de rendu du jeu
		 * \param keyboard : clavier initialis� dans Python3D
		 * \param mouse : souris initialis�e dans Python3D
		 * \param GUISystem : objet systeme CEGUI
		 * \param GUIRenderer : Gestionnaire d'interface utilisateur CEGUI
		 */
		EventListener(Ogre::SceneManager *sceneMgr, Ogre::RenderWindow *renderWindow, OIS::Keyboard *keyboard, OIS::Mouse *mouse, CEGUI::System *GUISystem, CEGUI::OgreCEGUIRenderer *GUIRenderer);
		/**
		 * \brief Destructeur
		 *
		 * Destructeur de la classe EventListener
		 */
        ~EventListener();

		/**
		 * \brief Callback de d�but d'image
		 *
		 * M�thode appel�e avant l'affichage de chaque image
		 *
		 * \param evt : informations sur l'image qui va �tre dessin�e
		 * \return true pour continuer, false pour sortir de la boucle de rendu
		 */
		bool frameStarted(const Ogre::FrameEvent &evt);

		/**
		 * \brief Une touche est appuy�e
		 *
		 * M�thode appel�e lorsqu'une touche du clavier est appuy�e
		 *
		 * \param e : informations sur la touche appuy�e
		 * \return true pour continuer, false pour sortir de la boucle de rendu
		 */
		bool keyPressed(const OIS::KeyEvent &e);
		/**
		 * \brief Une touche est relach�e
		 *
		 * M�thode appel�e lorsqu'une touche du clavier est relach�e
		 *
		 * \param e : informations sur la touche relach�e
		 * \return true pour continuer, false pour sortir de la boucle de rendu
		 */
        bool keyReleased(const OIS::KeyEvent &e);

		/**
		 * \brief La souris a boug�
		 *
		 * M�thode appel�e lorsque la souris a boug�
		 *
		 * \param e : informations sur le mouvement de la souris
		 * \return true pour continuer, false pour sortir de la boucle de rendu
		 */
        bool mouseMoved(const OIS::MouseEvent &e);
		/**
		 * \brief Un bouton de la souris est cliqu�
		 *
		 * M�thode appel�e lorsqu'un des boutons de la souris est appuy�
		 *
		 * \param e : informations sur la souris
		 * \param id : identifiant du bouton appuy�
		 * \return true pour continuer, false pour sortir de la boucle de rendu
		 */
        bool mousePressed(const OIS::MouseEvent &e, OIS::MouseButtonID id);
		/**
		 * \brief Un bouton de la souris est relach�
		 *
		 * M�thode appel�e lorsqu'un des boutons de la souris est relach�
		 *
		 * \param e : informations sur la souris
		 * \param id : identifiant du bouton relach�
		 * \return true pour continuer, false pour sortir de la boucle de rendu
		 */
        bool mouseReleased(const OIS::MouseEvent &e, OIS::MouseButtonID id);

		/**
		 * \brief Conversion OIS->CEGUI
		 *
		 * M�thode pour convertir un identifiant de bouton de souris OIS en identifiant CEGUI
		 *
		 * \param ois_button_id : identifiant OIS du bouton de souris � convertir
		 * \return CEGUI::LeftButton ; CEGUI::RightButton ; CEGUI::MiddleButton ; CEGUI::X1Button ; CEGUI::NoButton
		 */
		CEGUI::MouseButton OISToCEGUI(int ois_button_id);

		/**
		 * \brief Callback pour quitter
		 *
		 * Callback appel� par CEGUI lorsque le bouton "quitter" est cliqu�
		 * \return toujours true (n�cessaire pour le callback)
		 */
		bool onQuit(const CEGUI::EventArgs& e);
		/**
		 * \brief Callback pour jouer
		 *
		 * Callback appel� par CEGUI lorsque le bouton "jouer" est cliqu�
		 * \return toujours true (n�cessaire pour le callback)
		 */
		bool onPlay(const CEGUI::EventArgs& e);
		/**
		 * \brief Entr�e dans le jeu
		 *
		 * M�thode qui lance une nouvelle partie
		 */
		void onPlay();

		/**
		 * \brief Entr�e dans le menu principal
		 *
		 * M�thode qui g�re l'entr�e dans le menu principal, au lancement du jeu ou depuis le jeu
		 */
		void toMenu();
		/**
		 * \brief Callback pour retourner au menu
		 *
		 * Callback CEGUI qui appelle toMenu pour retourner au menu principal
		 * \return toujours true (n�cessaire pour le callback)
		 */
		bool toMenu(const CEGUI::EventArgs& e);

		/**
		 * \brief Gestion du menu de game over
		 *
		 * M�thode g�re l'affichage du menu lorsque la partie est perdue
		 */
		void gameOver();

		/**
		 * \brief Callback pour aller dans le menu du choix de vitesse
		 *
		 *	Callback CEGUI qui active le menu de choix de la vitesse de jeu
		 * \return toujours true (n�cessaire pour le callback)
		 */
		bool EventListener::toSpeed(const CEGUI::EventArgs& e);
		/**
		 * \brief Callback pour le choix de la vitesse
		 * 
		 * Callback CEGUI appel� lorsque le bouton de choix de la vitesse normale est cliqu�
		 * \return toujours true (n�cessaire pour le callback)
		 */
		bool toNormalSpeed(const CEGUI::EventArgs& e);
		/**
		 * \brief Callback pour le choix de la vitesse
		 * 
		 * Callback CEGUI appel� lorsque le bouton de choix de la vitesse rapide est cliqu�
		 * \return toujours true (n�cessaire pour le callback)
		 */
		bool toHighSpeed(const CEGUI::EventArgs& e);
		/**
		 * \brief Callback pour le choix de la vitesse
		 * 
		 * Callback CEGUI appel� lorsque le bouton de choix de la vitesse insane est cliqu�
		 * \return toujours true (n�cessaire pour le callback)
		 */
		bool toInsaneSpeed(const CEGUI::EventArgs& e);

		bool EventListener::onClear(const CEGUI::EventArgs &e);

	protected :
		/** Scene manager principal */
		Ogre::SceneManager *_SceneManager;
		/** Fenetre de rendu */
		Ogre::RenderWindow *_RenderWindow;

		/** Clavier */
		OIS::Keyboard *_Keyboard;
		/** Souris */
		OIS::Mouse *_Mouse; 

		/** objet syst�me CEGUI */
		CEGUI::System *_GUISystem;
		/** Gestionnaire d'interface utilisateur CEGUI */
		CEGUI::OgreCEGUIRenderer *_GUIRenderer;
		/** La fen�tre d'affichage des FPS */
		CEGUI::Window *_FPSWindow;
		/** La fr�quence de rafraichissement de l'affichage des FPS */
		int _FPSUpdateFreq;
		/** Compteur de frame avant rafraichissement de l'affichage des FPS */
		int _FPSSkippedFrames;
		/** Layout CEGUI pendant le jeu (fenetres fps et stats) */
		CEGUI::Window *_GameLayout;
		/** Layout CEGUI pendant le menu (fond, boutons quitter et jouer) */
		CEGUI::Window *_MenuLayout;
		/** Layout CEGUI pour le choix de la vitesse de jeu */
		CEGUI::Window *_MenuSpeedLayout;
		/** Layout CEGUI pendant pour le menu de fin de partie (boutons rejouer et retour au menu) */
		CEGUI::Window *_GameOverLayout;
		/** Timer pour calculer le temps de jeu */
		Ogre::Timer *_Timer;
		/** la fenetre dans laquelle on affiche le temps et la taille */
		CEGUI::Window *_TimerWindow;
		/** le nombre de secondes �coul�es depuis le d�but de la partie */
		int _Time;

		/** True pour continuer, false pour sortir de la boucle de rendu */
		bool _Continue;
		/** True si onPlay est appel� depuis le menu principal, false si il est appel� depuis le game over (bouton rejouer) */
		bool _FromMenu;

		/** d�termine quel sous-frameListener est actif \remark 0 : GameListener ; 1 : MenuListener*/
		int _Actif;
		/** frame listener du jeu */
		GameListener *_GameListener;
		
		/** gestionnaire de son */
		SoundManager *_SoundManager;

		/** le serpent */
		Snake *_Snake;
};

#endif // EVENTLISTENER_H

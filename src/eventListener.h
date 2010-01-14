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
 *  Cette classe s'occupe de récupérer les entrées clavier/souris et de les transferer au frame listener actif à chaque frame.
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
		 * \param keyboard : clavier initialisé dans Python3D
		 * \param mouse : souris initialisée dans Python3D
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
		 * \brief Callback de début d'image
		 *
		 * Méthode appelée avant l'affichage de chaque image
		 *
		 * \param evt : informations sur l'image qui va être dessinée
		 * \return true pour continuer, false pour sortir de la boucle de rendu
		 */
		bool frameStarted(const Ogre::FrameEvent &evt);

		/**
		 * \brief Une touche est appuyée
		 *
		 * Méthode appelée lorsqu'une touche du clavier est appuyée
		 *
		 * \param e : informations sur la touche appuyée
		 * \return true pour continuer, false pour sortir de la boucle de rendu
		 */
		bool keyPressed(const OIS::KeyEvent &e);
		/**
		 * \brief Une touche est relachée
		 *
		 * Méthode appelée lorsqu'une touche du clavier est relachée
		 *
		 * \param e : informations sur la touche relachée
		 * \return true pour continuer, false pour sortir de la boucle de rendu
		 */
        bool keyReleased(const OIS::KeyEvent &e);

		/**
		 * \brief La souris a bougé
		 *
		 * Méthode appelée lorsque la souris a bougé
		 *
		 * \param e : informations sur le mouvement de la souris
		 * \return true pour continuer, false pour sortir de la boucle de rendu
		 */
        bool mouseMoved(const OIS::MouseEvent &e);
		/**
		 * \brief Un bouton de la souris est cliqué
		 *
		 * Méthode appelée lorsqu'un des boutons de la souris est appuyé
		 *
		 * \param e : informations sur la souris
		 * \param id : identifiant du bouton appuyé
		 * \return true pour continuer, false pour sortir de la boucle de rendu
		 */
        bool mousePressed(const OIS::MouseEvent &e, OIS::MouseButtonID id);
		/**
		 * \brief Un bouton de la souris est relaché
		 *
		 * Méthode appelée lorsqu'un des boutons de la souris est relaché
		 *
		 * \param e : informations sur la souris
		 * \param id : identifiant du bouton relaché
		 * \return true pour continuer, false pour sortir de la boucle de rendu
		 */
        bool mouseReleased(const OIS::MouseEvent &e, OIS::MouseButtonID id);

		/**
		 * \brief Conversion OIS->CEGUI
		 *
		 * Méthode pour convertir un identifiant de bouton de souris OIS en identifiant CEGUI
		 *
		 * \param ois_button_id : identifiant OIS du bouton de souris à convertir
		 * \return CEGUI::LeftButton ; CEGUI::RightButton ; CEGUI::MiddleButton ; CEGUI::X1Button ; CEGUI::NoButton
		 */
		CEGUI::MouseButton OISToCEGUI(int ois_button_id);

		/**
		 * \brief Callback pour quitter
		 *
		 * Callback appelé par CEGUI lorsque le bouton "quitter" est cliqué
		 * \return toujours true (nécessaire pour le callback)
		 */
		bool onQuit(const CEGUI::EventArgs& e);
		/**
		 * \brief Callback pour jouer
		 *
		 * Callback appelé par CEGUI lorsque le bouton "jouer" est cliqué
		 * \return toujours true (nécessaire pour le callback)
		 */
		bool onPlay(const CEGUI::EventArgs& e);
		/**
		 * \brief Entrée dans le jeu
		 *
		 * Méthode qui lance une nouvelle partie
		 */
		void onPlay();

		/**
		 * \brief Entrée dans le menu principal
		 *
		 * Méthode qui gère l'entrée dans le menu principal, au lancement du jeu ou depuis le jeu
		 */
		void toMenu();
		/**
		 * \brief Callback pour retourner au menu
		 *
		 * Callback CEGUI qui appelle toMenu pour retourner au menu principal
		 * \return toujours true (nécessaire pour le callback)
		 */
		bool toMenu(const CEGUI::EventArgs& e);

		/**
		 * \brief Gestion du menu de game over
		 *
		 * Méthode gère l'affichage du menu lorsque la partie est perdue
		 */
		void gameOver();

		/**
		 * \brief Callback pour aller dans le menu du choix de vitesse
		 *
		 *	Callback CEGUI qui active le menu de choix de la vitesse de jeu
		 * \return toujours true (nécessaire pour le callback)
		 */
		bool EventListener::toSpeed(const CEGUI::EventArgs& e);
		/**
		 * \brief Callback pour le choix de la vitesse
		 * 
		 * Callback CEGUI appelé lorsque le bouton de choix de la vitesse normale est cliqué
		 * \return toujours true (nécessaire pour le callback)
		 */
		bool toNormalSpeed(const CEGUI::EventArgs& e);
		/**
		 * \brief Callback pour le choix de la vitesse
		 * 
		 * Callback CEGUI appelé lorsque le bouton de choix de la vitesse rapide est cliqué
		 * \return toujours true (nécessaire pour le callback)
		 */
		bool toHighSpeed(const CEGUI::EventArgs& e);
		/**
		 * \brief Callback pour le choix de la vitesse
		 * 
		 * Callback CEGUI appelé lorsque le bouton de choix de la vitesse insane est cliqué
		 * \return toujours true (nécessaire pour le callback)
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

		/** objet système CEGUI */
		CEGUI::System *_GUISystem;
		/** Gestionnaire d'interface utilisateur CEGUI */
		CEGUI::OgreCEGUIRenderer *_GUIRenderer;
		/** La fenêtre d'affichage des FPS */
		CEGUI::Window *_FPSWindow;
		/** La fréquence de rafraichissement de l'affichage des FPS */
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
		/** le nombre de secondes écoulées depuis le début de la partie */
		int _Time;

		/** True pour continuer, false pour sortir de la boucle de rendu */
		bool _Continue;
		/** True si onPlay est appelé depuis le menu principal, false si il est appelé depuis le game over (bouton rejouer) */
		bool _FromMenu;

		/** détermine quel sous-frameListener est actif \remark 0 : GameListener ; 1 : MenuListener*/
		int _Actif;
		/** frame listener du jeu */
		GameListener *_GameListener;
		
		/** gestionnaire de son */
		SoundManager *_SoundManager;

		/** le serpent */
		Snake *_Snake;
};

#endif // EVENTLISTENER_H

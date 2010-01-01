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
		 * \param snake : le serpent
		 */
		EventListener(Ogre::SceneManager *sceneMgr, Ogre::RenderWindow *renderWindow, OIS::Keyboard *keyboard, OIS::Mouse *mouse, CEGUI::System *GUISystem, CEGUI::OgreCEGUIRenderer *GUIRenderer, Snake *snake);
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
		 * \return CEGUI::LeftButton;CEGUI::RightButton;CEGUI::MiddleButton;CEGUI::X1Button;CEGUI::NoButton
		 */
		CEGUI::MouseButton OISToCEGUI(int ois_button_id);

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
		/** DEBUG ONLY - la fen�tre d'affichage des FPS */
		CEGUI::Window *_FPSWindow;
		/** DEBUG ONLY - la fr�quence de rafraichissement de l'affichage des FPS */
		int _FPSUpdateFreq;
		/** DEBUG ONLY - compteur de frame avant rafraichissement de l'affichage des FPS */
		int _FPSSkippedFrames;

		/** True pour continuer, false pour sortir de la boucle de rendu */
		bool _Continue;

		/** d�termine quel sous-frameListener est actif \remark 0 : GameListener ; 1 : MenuListener*/
		int _Actif;
		/** frame listener du jeu */
		GameListener *_GameListener;
		/** frame listener du menu */
		MenuListener *_MenuListener;
		
		/** gestionnaire de son */
		SoundManager *_SoundManager;

		/** le serpent */
		Snake *_Snake;
};

#endif // EVENTLISTENER_H

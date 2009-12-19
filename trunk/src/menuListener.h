/*
-------------------------------------------------------------------------------
This file is part of Python3D.

Copyright (c) 2009 Emilien Dupont
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
 * \file menuListener.h
 * \brief Le frame listener qui s'occupe de la gestion des �v�nements dans le menu
 * \author Emilien Dupont
 */

#ifndef MENULISTENER_H
#define MENULISTENER_H

#include <ogre.h>
#include <OIS/OIS.h>

/**
 * \class MenuListener
 * \brief frame listener du menu
 *
 *  Cette classe s'occupe de r�cup�rer les entr�es clavier/souris et de les traiter dans le menu
 */
class MenuListener
{
    public:
		/**
		 * \brief Constructeur
		 *
		 * Constructeur de la classe MenuListener
		 */
		MenuListener();
		/**
		 * \brief Destructeur
		 *
		 * Destructeur de la classe MenuListener
		 */
        ~MenuListener();

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
};

#endif // MENULISTENER_H

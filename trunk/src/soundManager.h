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
 * \file soundManager.h
 * \brief SoundManager : le gestionnaire de son
 * \author Emilien Dupont
 */

#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include <ogre.h>
#include <FMOD/fmod.hpp>
#include <FMOD/fmod_errors.h>

/**
 * \class SoundManager
 * \brief gestionnaire de son
 *
 *  Cette classe g�re l'initialisation du syst�me audio (FMOD) et la lecture de sons et de musiques
 */
class SoundManager
{
	public:
		/**
		 * \brief Constructeur
		 *
		 * Constructeur de la classe SoundManager.
		 */
		SoundManager();
		/**
		 * \brief Destructeur
		 *
		 * Destructeur de la classe SoundManager.
		 */
		~SoundManager();

		/**
		 * \brief Chargement des ressources
		 *
		 * M�thode qui charge tous les sons et toutes les musiques
		 */
		void loadResources();

		/**
		 * \brief Jouer un son
		 *
		 * M�thode appel�e pour lancer la lecture d'un son
		 *
		 * \param sound : num�ro du son � jouer.
		 */
		void playSound(int sound);
		/**
		 * \brief Jouer une musique
		 *
		 * M�thode appel�e pour lancer la lecture d'une musique.
		 *
		 * \param track : num�ro de la musique � jouer
		 */
		void playStream(int track);
		/**
		 * \brief Stopper une musique
		 *
		 * M�thode appel�e pour stopper une musique
		 *
		 * \param track : num�ro de la musique � arreter
		 */
		void stopStream(int track);

		/**
		 * \brief Mettre � jour le gestionnaire de son
		 *
		 * M�thode � appeler une fois par image, elle sert � mettre � jour le syst�me FMOD.
		 */
		void update();

	protected:
		/** Objet syst�me FMOD */
		FMOD::System *_FMODSystem;
		/** Tableau contenant les flux vers les musiques du jeu (sons longs)*/
		FMOD::Sound *_Music[2];
		/** Canaux dans lesquels sont jou�s les flux */
		FMOD::Channel *_MusicChan[2];
		/** Tableau contenant les sons du jeu (sons courts)*/
		FMOD::Sound *_Sound[2];
};

#endif // SOUNDMANAGER_H

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

#include "soundManager.h"

SoundManager::SoundManager()
{
	FMOD::System_Create(&_FMODSystem);
	_FMODSystem->init(10, FMOD_INIT_NORMAL, 0);

	_FMODSystem->createSound("../media/audio/test_son_1.wav", FMOD_3D, 0, &_Sound[0]);
	_FMODSystem->createSound("../media/audio/test_son_2.wav", FMOD_3D, 0, &_Sound[1]);
	_FMODSystem->createStream("../media/audio/test_music_1.ogg", FMOD_3D, 0, &_Music[0]);
	_FMODSystem->createStream("../media/audio/test_music_2.ogg", FMOD_3D, 0, &_Music[1]);
}

SoundManager::~SoundManager()
{
	_Sound[0]->release();
	_Sound[1]->release();
	_Music[0]->release();
	_Music[1]->release();

	_FMODSystem->release();
}

void SoundManager::playSound(int sound)
{
	_FMODSystem->playSound(FMOD_CHANNEL_FREE, _Sound[sound], false, 0);
}

void SoundManager::playStream(int track)
{
	_FMODSystem->playSound(FMOD_CHANNEL_FREE, _Music[track], false, &_MusicChan[track]);
}

void SoundManager::update()
{
	_FMODSystem->update();
}

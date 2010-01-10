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

#include "soundManager.h"

void ERRCHECK(FMOD_RESULT result)
{
    if (result != FMOD_OK)
		throw std::runtime_error("FMOD error ! " + Ogre::StringConverter::toString(result) + " " + FMOD_ErrorString(result));
}

SoundManager::SoundManager()
{
    int numdrivers;
    FMOD_SPEAKERMODE speakermode;
    FMOD_CAPS caps;
    char name[256];

    ERRCHECK(FMOD::System_Create(&_FMODSystem));
    
    ERRCHECK(_FMODSystem->getNumDrivers(&numdrivers));
    if (numdrivers == 0)
    {
        ERRCHECK(_FMODSystem->setOutput(FMOD_OUTPUTTYPE_NOSOUND));
    }
    else
    {
        ERRCHECK(_FMODSystem->getDriverCaps(0, &caps, 0, 0, &speakermode));
        ERRCHECK(_FMODSystem->setSpeakerMode(speakermode));

        if (caps & FMOD_CAPS_HARDWARE_EMULATED)
            ERRCHECK(_FMODSystem->setDSPBufferSize(1024, 10));

        ERRCHECK(_FMODSystem->getDriverInfo(0, name, 256, 0));

        if (strstr(name, "SigmaTel"))
            ERRCHECK(_FMODSystem->setSoftwareFormat(48000, FMOD_SOUND_FORMAT_PCMFLOAT, 0,0, FMOD_DSP_RESAMPLER_LINEAR));
    }

    if (_FMODSystem->init(16, FMOD_INIT_NORMAL, 0) == FMOD_ERR_OUTPUT_CREATEBUFFER)
    {
        ERRCHECK(_FMODSystem->setSpeakerMode(FMOD_SPEAKERMODE_STEREO));
        ERRCHECK(_FMODSystem->init(16, FMOD_INIT_NORMAL, 0));
    }

	_Track = -1;
	_Type = "none";
	loadResources();
}

SoundManager::~SoundManager()
{
	for(int i = 0; i < NB_SOUND; ++i)
		ERRCHECK(_Sound[i]->release());
	for(int i = 0; i < TRACK_MENU; ++i)
		ERRCHECK(_MenuMusic[i]->release());
	for(int i = 0; i < TRACK_GAME; ++i)
		ERRCHECK(_GameMusic[i]->release());

	ERRCHECK(_FMODSystem->release());
}

void SoundManager::loadResources()
{
	ERRCHECK(_FMODSystem->createSound("../media/audio/click.wav", FMOD_DEFAULT, 0, &_Sound[0]));
	ERRCHECK(_FMODSystem->createSound("../media/audio/click1.wav", FMOD_DEFAULT, 0, &_Sound[1]));
	ERRCHECK(_FMODSystem->createSound("../media/audio/screenshot.wav", FMOD_DEFAULT, 0, &_Sound[2]));
	ERRCHECK(_FMODSystem->createSound("../media/audio/ready_go.wav", FMOD_DEFAULT, 0, &_Sound[3]));
	ERRCHECK(_FMODSystem->createSound("../media/audio/game_over.wav", FMOD_DEFAULT, 0, &_Sound[4]));
	ERRCHECK(_FMODSystem->createSound("../media/audio/game_over_boom.wav", FMOD_DEFAULT, 0, &_Sound[5]));
	ERRCHECK(_FMODSystem->createSound("../media/audio/bip1.wav", FMOD_DEFAULT, 0, &_Sound[6]));
	ERRCHECK(_FMODSystem->createSound("../media/audio/bip2.wav", FMOD_DEFAULT, 0, &_Sound[7]));
	ERRCHECK(_FMODSystem->createSound("../media/audio/bip3.wav", FMOD_DEFAULT, 0, &_Sound[8]));

	std::string filename;
	for(int i = 0; i < TRACK_MENU; ++i)
	{
		filename = "../media/audio/menu" + Ogre::StringConverter::toString(i) + ".ogg";
		ERRCHECK(_FMODSystem->createStream(filename.c_str(), FMOD_DEFAULT, 0, &_MenuMusic[i]));
	}

	for(int i = 0; i < TRACK_GAME; ++i)
	{
		filename = "../media/audio/game" + Ogre::StringConverter::toString(i) + ".ogg";
		ERRCHECK(_FMODSystem->createStream(filename.c_str(), FMOD_DEFAULT, 0, &_GameMusic[i]));
	}
}

void SoundManager::playSound(int sound)
{
	if(sound < NB_SOUND)
		ERRCHECK(_FMODSystem->playSound(FMOD_CHANNEL_FREE, _Sound[sound], false, 0));
}

void SoundManager::playStream(std::string type, int track)
{
	if(type == "menu")
	{
		if(track < TRACK_MENU)
			ERRCHECK(_FMODSystem->playSound(FMOD_CHANNEL_FREE, _MenuMusic[track], false, &_MenuMusicChan[track]));
	}
	else if(type == "game")
	{
		if(track < TRACK_GAME)
			ERRCHECK(_FMODSystem->playSound(FMOD_CHANNEL_FREE, _GameMusic[track], false, &_GameMusicChan[track]));
	}

	_Track = track;
	_Type = type;
}

void SoundManager::stopStream()
{
	int track = 0;
	while(track < TRACK_MENU)
	{
		bool playing;
		_MenuMusicChan[track]->isPlaying(&playing);
		if(playing)
			ERRCHECK(_MenuMusicChan[track]->stop());
		++track;
	}

	track = 0;
	while(track < TRACK_GAME)
	{
		bool playing;
		_GameMusicChan[track]->isPlaying(&playing);
		if(playing)
			ERRCHECK(_GameMusicChan[track]->stop());
		++track;
	}

	_Track = -1;
	_Type = "none";
}

void SoundManager::update()
{
	if(_Track != -1)
	{
		if(_Type == "menu")
		{
			bool playing;
			_MenuMusicChan[_Track]->isPlaying(&playing);
			if(!playing)
			{
				if(_Track >= TRACK_MENU - 1)
				{
					playStream("menu", 0);
				}
				else
				{
					playStream("menu", _Track + 1);
				}
			}
		}
		else if(_Type == "game")
		{
			bool playing;
			_GameMusicChan[_Track]->isPlaying(&playing);
			if(!playing)
			{
				if(_Track >= TRACK_GAME - 1)
				{
					playStream("game", 0);
				}
				else
				{
					playStream("game", _Track + 1);
				}
			}
		}
	}

	_FMODSystem->update();
}

int SoundManager::getNbTrack(std::string type)
{
	if(type == "game")
		return TRACK_GAME;
	else
		return TRACK_MENU;
}

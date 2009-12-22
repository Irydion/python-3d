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

	loadResources();
}

SoundManager::~SoundManager()
{
	ERRCHECK(_Sound[0]->release());
	ERRCHECK(_Sound[1]->release());
	ERRCHECK(_Music[0]->release());
	ERRCHECK(_Music[1]->release());

	ERRCHECK(_FMODSystem->release());
}

void SoundManager::loadResources()
{
	ERRCHECK(_FMODSystem->createSound("../media/audio/test_son_1.wav", FMOD_3D, 0, &_Sound[0]));
	ERRCHECK(_FMODSystem->createSound("../media/audio/test_son_2.wav", FMOD_3D, 0, &_Sound[1]));
	ERRCHECK(_FMODSystem->createStream("../media/audio/test_music_1.ogg", FMOD_3D, 0, &_Music[0]));
	ERRCHECK(_FMODSystem->createStream("../media/audio/test_music_2.ogg", FMOD_3D, 0, &_Music[1]));
}

void SoundManager::playSound(int sound)
{
	ERRCHECK(_FMODSystem->playSound(FMOD_CHANNEL_FREE, _Sound[sound], false, 0));
}

void SoundManager::playStream(int track)
{
	ERRCHECK(_FMODSystem->playSound(FMOD_CHANNEL_FREE, _Music[track], false, &_MusicChan[track]));
}

void SoundManager::stopStream(int track)
{
	ERRCHECK(_MusicChan[track]->stop());
}

void SoundManager::update()
{
	_FMODSystem->update();
}

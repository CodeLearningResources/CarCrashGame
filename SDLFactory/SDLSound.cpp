/*
 * SDLSound.cpp
 *
 *  Created on: 4-apr.-2015
 *      Author: Thomas
 */

#include "SDLSound.h"

using namespace CCG_SDL;

SDLSound::SDLSound()
{
	sound = NULL;
}

SDLSound::SDLSound(Mix_Chunk* sound)
{
	this->sound = sound;
}

SDLSound::~SDLSound()
{
	free();
}

void SDLSound::setSound(Mix_Chunk* sound)
{
	//Unload pre-existing sound
	free();

	this->sound = sound;
}

void SDLSound::free()
{
	//Free sound if existing
	if(sound != NULL)
	{
		Mix_FreeChunk(sound);
		sound = NULL;
	}
}

Mix_Chunk* SDLSound::getSound()
{
	return sound;
}

void SDLSound::playSound()
{
	if(this->sound != NULL)
	{
		Mix_PlayChannel(-1, this->sound, 0);
	}
}

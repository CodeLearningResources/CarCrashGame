/*
 * SDLMusic.cpp
 *
 *  Created on: 4-apr.-2015
 *      Author: Thomas
 */

#include "SDLMusic.h"
#include "stdio.h"
using namespace CCG_SDL;

SDLMusic::SDLMusic() : CCG::Music()
{
	music = NULL;
	playing = false;
}

SDLMusic::SDLMusic(Mix_Music* music) : CCG::Music()
{
	this->music = music;
	this->playing = false;
}

SDLMusic::~SDLMusic()
{
	free();
}

void SDLMusic::setMusic(Mix_Music* music)
{
	//Unload pre-existing music
	free();

	this->music = music;
}

void SDLMusic::free()
{
	//Free music if existing
	if(music != NULL)
	{
		Mix_FreeMusic(music);
		music = NULL;
	}
}

void SDLMusic::setPlayState(bool flag)
{
	this->playing = flag;

	if(flag)
	{
		this->playTime.start();
	}
	else
	{
		this->playTime.pause();
	}
}

bool SDLMusic::getPlayState()
{
	return this->playing;
}

Uint32 SDLMusic::getPlayPosition()
{
	return this->playTime.getTicks();
}

Uint32 SDLMusic::getMusicLength()
{
	/*
	Uint32 sPoints = 0;
	Uint32 sFrames = 0;
	int sFrequency = 0;
	Uint16 format = 0;
	int channels = 0;

	//Get sample frequency, format and channels
	if(!Mix_QuerySpec(&sFrequency, &format, &channels))
	{
		return -1; //Audio device is not initialized
	}

	//Sample points = bytes / sample size
	Mix_Chunk* chunk;
	//sPoints = (this->music->alen / ((format & 0xFF) / 8));
	*/
	return 0;
}

Mix_Music* SDLMusic::getMusic()
{
	return music;
}

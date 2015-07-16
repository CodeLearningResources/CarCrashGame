/*
 * SDLMusicPlayer.cpp
 *
 *  Created on: 14-apr.-2015
 *      Author: Thomas
 */

#include "SDLMusicPlayer.h"
#include "stdio.h"
using namespace CCG_SDL;

SDLMusicPlayer::SDLMusicPlayer() : CCG::MusicPlayer()
{
	playList = new std::vector<SDLMusic*>();
	mixTrack = false;
	nextMusicGradually = false;
	fadeIn = 0;
	fadeOut = 0;
}

SDLMusicPlayer::~SDLMusicPlayer()
{
	this->releasePlaylist();

	delete(playList);
}

void SDLMusicPlayer::setMusic(CCG::Music* music)
{
	//Clear the playlist
	this->releasePlaylist();

	//Set the new music on the playlist
	this->playList->push_back((SDLMusic*) music);
}

void SDLMusicPlayer::pushMusic(CCG::Music* music)
{
	//Stop the musicplayer
	if(Mix_PlayingMusic())
	{
		Mix_FadeOutMusic(fadeOut);
	}

	//Add music to the playlist stack
	this->playList->push_back((SDLMusic*)music);
}

void SDLMusicPlayer::popMusic()
{
	if(!playList->empty())
	{
		//Stop the musicplayer
		if(Mix_PlayingMusic())
		{
			Mix_FadeOutMusic(fadeOut);
		}

		this->playList->pop_back();

		if(!playList->empty())
		{
			if(playList->back()->getPlayState())
			{
				this->startMusic(true);
			}
		}
	}
}

void SDLMusicPlayer::releasePlaylist()
{
	//Stop the musicplayer
	this->stopMusic(false);

	//Clear the playlist stack
	while(!playList->empty())
	{
		playList->pop_back();
	}
}

void SDLMusicPlayer::startMusic(bool gradually)
{
	SDLMusic* music;

	//Set the playstate of the current track to true
	if(!playList->empty())
	{
		music = playList->back();

		if(music->getMusic() == NULL)
		{
			//No music file available
			return;
		}
		else
		{
			if(gradually)
			{
				Mix_FadeInMusic(music->getMusic(), -1, fadeIn);
			}
			else
			{
				Mix_PlayMusic(music->getMusic(), -1);
			}

			//Play from last play position
			//Mix_RewindMusic();
			//Mix_SetMusicPosition(music->getPlayPosition());

			playList->back()->setPlayState(true);
		}
	}
}

void SDLMusicPlayer::resumeMusic()
{
	SDLMusic* music;

	//Set the playstate of the current track to true
	if(!playList->empty())
	{
		music = playList->back();

		music->setPlayState(true);

		if(music->getMusic() == NULL)
		{
			//No music file available
			return;
		}
		else
		{
			if(Mix_PlayingMusic())
			{
				Mix_ResumeMusic();
			}
			else
			{
				Mix_PlayMusic(music->getMusic(), -1);
			}

			//Play from last play position
			//Mix_RewindMusic();
			//Mix_SetMusicPosition(music->getPlayPosition());
		}
	}
}

void SDLMusicPlayer::pauseMusic()
{
	//Set the playstate of the current track to false
	if(!playList->empty())
	{
		playList->back()->setPlayState(false);
	}

	Mix_PauseMusic();
}

void SDLMusicPlayer::rewindMusic()
{
	Mix_RewindMusic();
}

void SDLMusicPlayer::stopMusic(bool gradually)
{
	//Set the playstate of the current track to false
	if(!playList->empty())
	{
		playList->back()->setPlayState(false);
	}

	if(gradually)
	{
		Mix_FadeOutMusic(fadeOut);
	}
	else
	{
		Mix_HaltMusic();
	}
}

void SDLMusicPlayer::pauseSFXSounds()
{
	Mix_Pause(-1);
}

void SDLMusicPlayer::resumeSFXSounds()
{
	Mix_Resume(-1);
}

void SDLMusicPlayer::setMusicVolume(int volume)
{
	int mixVolume = (MIX_MAX_VOLUME / 100.0f) * volume + 0.5;						//Float to int round correction: +0.5

	Mix_VolumeMusic(mixVolume);
}

void SDLMusicPlayer::setSFXVolume(int volume)
{
	int mixVolume = (MIX_MAX_VOLUME / 100.0f) * volume + 0.5;						//Float to int round correction: +0.5

	Mix_Volume(-1, mixVolume);
}

void SDLMusicPlayer::setFadeOutTime(int fadeOut)
{
	this->fadeOut = fadeOut;
}

void SDLMusicPlayer::setFadeInTime(int fadeIn)
{
	this->fadeIn = fadeIn;
}

int SDLMusicPlayer::getMusicVolume()
{
	int mixVolume = ((Mix_VolumeMusic(-1) * 1.0f) / MIX_MAX_VOLUME) * 100 + 0.5;	//Float to int round correction: +0.5

	return mixVolume;
}

int SDLMusicPlayer::getSFXVolume()
{
	int mixVolume = ((Mix_Volume(-1, -1) * 1.0f) / MIX_MAX_VOLUME) * 100 + 0.5;		//Float to int round correction: +0.5

	return mixVolume;
}

int SDLMusicPlayer::getFadeOutTime()
{
	return this->fadeOut;
}

int SDLMusicPlayer::getFadeInTime()
{
	return this->fadeIn;
}

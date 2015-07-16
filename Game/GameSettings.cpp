/*
 * GameSettings.cpp
 *
 *  Created on: 20-jun.-2015
 *      Author: Thomas
 */

#include "GameSettings.h"

using namespace CCG;

GameSettings::GameSettings()
{
	//Game
	musicVolume = 100;
	SFXVolume = 100;
	FPSCap = 0;
	VSync = true;

	//Controls
	controlsPlayer01 = new KeyboardKey*[PLAYER_CONTROL_MAX]();

	controlsPlayer01[PLAYER_CONTROL_UP] = new KeyboardKey(KEY_Z);
	controlsPlayer01[PLAYER_CONTROL_RIGHT] = new KeyboardKey(KEY_D);
	controlsPlayer01[PLAYER_CONTROL_DOWN] = new KeyboardKey(KEY_S);
	controlsPlayer01[PLAYER_CONTROL_LEFT] = new KeyboardKey(KEY_Q);
	//controlsPlayer01[PLAYER_CONTROL_NITRO] = new KeyboardKey(KEY_SPACE);
	controlsPlayer01[PLAYER_CONTROL_ROCKET] = new KeyboardKey(KEY_R);
}

GameSettings::GameSettings(int musicVolume, int SFXVolume, int FPSCap, bool VSync, KeyboardKey** controlsPlayer01)
{
	//Game
	this->musicVolume = musicVolume;
	this->SFXVolume = SFXVolume;
	this->FPSCap = FPSCap;
	this->VSync = VSync;

	//Controls
	this->controlsPlayer01 = new KeyboardKey*[PLAYER_CONTROL_MAX]();

	for(int i = 0; i < PLAYER_CONTROL_MAX; i++)
	{
		this->controlsPlayer01[i] = new KeyboardKey(*controlsPlayer01[i]);
	}
}

GameSettings::GameSettings(const GameSettings& settings)
{
	this->musicVolume = settings.musicVolume;
	this->SFXVolume = settings.SFXVolume;
	this->FPSCap = settings.FPSCap;
	this->VSync = settings.VSync;
	this->controlsPlayer01 = new KeyboardKey*[PLAYER_CONTROL_MAX]();

	for(int i = 0; i < PLAYER_CONTROL_MAX; i++)
	{
		this->controlsPlayer01[i] = new KeyboardKey(*settings.controlsPlayer01[i]);
	}
}

GameSettings::~GameSettings()
{
	for(int i = 0; i < PLAYER_CONTROL_MAX; i++)
	{
		delete(this->controlsPlayer01[i]);

		this->controlsPlayer01[i] = NULL;
	}

	delete(this->controlsPlayer01);
}


int GameSettings::getMusicVolume()
{
	return this->musicVolume;
}

int GameSettings::getSFXVolume()
{
	return this->SFXVolume;
}

int GameSettings::getFPSCap()
{
	return this->FPSCap;
}

bool GameSettings::getVSyncActive()
{
	return this->VSync;
}

KeyboardKey** GameSettings::getControlsPlayer(int player)
{
	if(player == 1)
	{
		return this->controlsPlayer01;
	}
	else
	{
		return NULL;
	}
}


void GameSettings::setMusicVolume(int volume)
{
	if(volume >= 0 && volume <= 100)
		this->musicVolume = volume;
}

void GameSettings::setSFXVolume(int volume)
{
	if(volume >= 0 && volume <= 100)
		this->SFXVolume = volume;
}

void GameSettings::setFPSCap(int cap)
{
	if(cap >= 0)
		this->FPSCap = cap;
}

void GameSettings::setVSync(bool flag)
{
	this->VSync = flag;
}

void GameSettings::setControlsPlayer(KeyboardKey** controls, int player)
{
	KeyboardKey** selectedPlayerControl;

	switch(player)
	{
		case 1:
			selectedPlayerControl = this->controlsPlayer01;
			break;
		default:
			selectedPlayerControl = NULL;
			break;
	}

	if(selectedPlayerControl != NULL)
	{
		for(int i = 0; i < PLAYER_CONTROL_MAX; i++)
		{
			*selectedPlayerControl[i] = *controls[i];
		}
	}
}

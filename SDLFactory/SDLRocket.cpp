/*
 * SDLRocket.cpp
 *
 *  Created on: 8-jun.-2015
 *      Author: Thomas
 */

#include "SDLRocket.h"

using namespace CCG_SDL;

SDLRocket::SDLRocket() : Rocket()
{
	renderer = NULL;
	texture = NULL;
	launchSound = NULL;
	visibility = false;
}

SDLRocket::SDLRocket(SDL_Renderer* renderer, SDLTexture* texture, SDLSound* launchSound)
{
	this->renderer = renderer;
	this->texture = texture;
	this->launchSound = launchSound;
	this->visibility = false;
}

SDLRocket::~SDLRocket()
{
	//Destruct SDLRocket object
}

void SDLRocket::setTexture(SDLTexture* texture)
{
	this->texture = texture;
}

SDLTexture* SDLRocket::getTexture()
{
	return this->texture;
}

void SDLRocket::visible(bool flag)
{
	this->visibility = flag;
}

bool SDLRocket::isVisible()
{
	return this->visibility;
}

void SDLRocket::update()
{
	if(texture == NULL)
	{
		return;
	}

	if(visibility)
	{
		SDL_Rect renderBox = {(int)getPosX(), (int)getPosY(), (int)getSizeX(), (int)getSizeY()};
		SDL_RenderCopyEx(renderer, texture->getTexture(), NULL, &renderBox, getRotation() + getRelRotation(), NULL, SDL_FLIP_NONE);
	}
}

void SDLRocket::playLaunchSound()
{
	this->launchSound->playSound();
}

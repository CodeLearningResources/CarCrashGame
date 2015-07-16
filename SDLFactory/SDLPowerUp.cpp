/*
 * SDLPowerUp.cpp
 *
 *  Created on: 19-apr.-2015
 *      Author: Thomas
 */

#include "SDLPowerUp.h"

using namespace CCG_SDL;

SDLPowerUp::SDLPowerUp() : CCG::PowerUp()
{
	this->visibility = false;
	this->texture = NULL;
	this->renderer = NULL;
}

SDLPowerUp::SDLPowerUp(SDL_Renderer* renderer, SDLTexture* texture, CCG::PowerUpBonus bonus) : CCG::PowerUp(bonus)
{
	this->visibility = false;
	this->texture = texture;
	this->renderer = renderer;
}

SDLPowerUp::~SDLPowerUp()
{
	//Destruct SDLPowerUp object
}

void SDLPowerUp::setTexture(SDLTexture* texture)
{
	this->texture = texture;
}

SDLTexture* SDLPowerUp::getTexture()
{
	return this->texture;
}

void SDLPowerUp::visible(bool flag)
{
	this->visibility = flag;
}

bool SDLPowerUp::isVisible()
{
	return this->visibility;
}

void SDLPowerUp::update()
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

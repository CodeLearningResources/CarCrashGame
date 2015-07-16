/*
 * SDLCar.cpp
 *
 *  Created on: 9-mrt.-2015
 *      Author: Thomas
 */

#include "SDLCar.h"

using namespace CCG_SDL;

//Default constructor
SDLCar::SDLCar(void) : CCG::Car()
{
	this->visibility = false;
	this->texture = NULL;
	this->crashSound = NULL;
	this->renderer = NULL;
}

SDLCar::SDLCar(SDL_Renderer* renderer, SDLTexture* texture, SDLSound* crashSound) : CCG::Car()
{
	this->visibility = false;
	this->texture = texture;
	this->crashSound = crashSound;
	this->renderer = renderer;
}

//Copy constructor
SDLCar::SDLCar(const SDLCar& car) : CCG::Car(car.getHealth(), car.getNitro())
{
	this->visibility = car.visibility;
	this->texture = car.texture;
	this->crashSound = car.crashSound;
	this->renderer = car.renderer;
}

//Destructor
SDLCar::~SDLCar()
{
	//Destruct SDLCar object
}

void SDLCar::setTexture(SDLTexture* texture)
{
	this->texture = texture;
}

SDLTexture* SDLCar::getTexture()
{
	return texture;
}

void SDLCar::visible(bool flag)
{
	this->visibility = flag;
}

bool SDLCar::isVisible()
{
	return this->visibility;
}

void SDLCar::update()
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

void SDLCar::playCrashSound()
{
	this->crashSound->playSound();
}

void SDLCar::playNitroSound()
{

}

void SDLCar::stopNitroSound()
{

}

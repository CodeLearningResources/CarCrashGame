/*
 * SDLPicture.cpp
 *
 *  Created on: 16-apr.-2015
 *      Author: Thomas
 */

#include "SDLPicture.h"

using namespace CCG_SDL;

//Default constructor
SDLPicture::SDLPicture(void) : CCG::Picture()
{
	this->visibility = false;
	this->texture = NULL;
	this->renderer = NULL;
}

SDLPicture::SDLPicture(SDL_Renderer* renderer, SDLTexture* texture) : CCG::Picture()
{
	this->visibility = false;
	this->texture = texture;
	this->renderer = renderer;
}

//Copy constructor
SDLPicture::SDLPicture(const SDLPicture& picture) : CCG::Picture()
{
	this->visibility = picture.visibility;
	this->texture = picture.texture;
	this->renderer = picture.renderer;
}

//Destructor
SDLPicture::~SDLPicture()
{
	//Destruct SDLPicture object
}

void SDLPicture::setTexture(SDLTexture* texture)
{
	this->texture = texture;
}

SDLTexture* SDLPicture::getTexture()
{
	return texture;
}

void SDLPicture::visible(bool flag)
{
	this->visibility = flag;
}

bool SDLPicture::isVisible()
{
	return this->visibility;
}

void SDLPicture::update()
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

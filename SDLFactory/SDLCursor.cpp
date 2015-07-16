/*
 * SDLCursor.cpp
 *
 *  Created on: 19-jun.-2015
 *      Author: Thomas
 */

#include "SDLCursor.h"

using namespace CCG_SDL;

//Default constructor
SDLCursor::SDLCursor(void) : CCG::Cursor()
{
	this->visibility = false;
	this->textures = new SDLTexture*[CCG::CURSOR_STATE_MAX]();
	this->renderer = NULL;
}

SDLCursor::SDLCursor(SDL_Renderer* renderer, SDLTexture** texturePack) : CCG::Cursor()
{
	this->visibility = false;
	this->textures = new SDLTexture*[CCG::CURSOR_STATE_MAX]();
	this->renderer = renderer;

	this->setTexture(texturePack);
}

//Destructor
SDLCursor::~SDLCursor()
{
	delete(textures);
	textures = NULL;
}

void SDLCursor::setTexture(SDLTexture** texturePack)
{
	for(int i = 0; i < CCG::CURSOR_STATE_MAX; i++)
	{
		this->textures[i] = texturePack[i];
	}
}

void SDLCursor::visible(bool flag)
{
	this->visibility = flag;
}

bool SDLCursor::isVisible()
{
	return this->visibility;
}

void SDLCursor::update()
{
	if(textures[this->getCursorState()] == NULL)
	{
		return;
	}

	if(visibility)
	{
		SDL_Rect renderBox = {(int)getPosX(), (int)getPosY(), (int)getSizeX(), (int)getSizeY()};
		SDL_RenderCopyEx(renderer, textures[this->getCursorState()]->getTexture(), NULL, &renderBox, getRotation() + getRelRotation(), NULL, SDL_FLIP_NONE);
	}
}

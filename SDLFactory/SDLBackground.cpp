/*
 * SDLBackground.cpp
 *
 *  Created on: 16-mrt.-2015
 *      Author: Thomas
 */

#include "SDLBackground.h"

using namespace CCG_SDL;

SDLBackground::SDLBackground() : CCG::Background()
{
	visibility = false;
	texture = NULL;
	renderer = NULL;
}

SDLBackground::SDLBackground(SDL_Renderer* renderer, SDLTexture* texture, CCG::ScrollDirection direction) : CCG::Background(direction)
{
	this->visibility = false;
	this->texture = texture;
	this->renderer = renderer;
}

//Copy constructor
SDLBackground::SDLBackground(const SDLBackground& background) : CCG::Background(background.getScrollDirection())
{
	this->visibility = background.visibility;
	this->texture = background.texture;
	this->renderer = background.renderer;
}

SDLBackground::~SDLBackground()
{

}

void SDLBackground::setTexture(SDLTexture* texture)
{
	this->texture = texture;
}

SDLTexture* SDLBackground::getTexture()
{
	return texture;
}

void SDLBackground::visible(bool flag)
{
	this->visibility = flag;
}

bool SDLBackground::isVisible()
{
	return visibility;
}

void SDLBackground::update()
{
	if(texture == NULL)
	{
		return;
	}

	if(visibility)
	{
		CCG::ScrollDirection direction = getScrollDirection();
		float posXCopy = getPosX();
		float posYCopy = getPosY();

		if(direction == CCG::SCROLL_HORIZONTAL || direction == CCG::SCROLL_DIAGONAL_FIRST || direction == CCG::SCROLL_DIAGONAL_SECOND)
		{
			//Horizontal scroll
			if(getPosX() < 0)
			{
				posXCopy += getSizeX();
			}
			else
			{
				posXCopy -= getSizeX();
			}
		}

		if(direction == CCG::SCROLL_VERTICAL || direction == CCG::SCROLL_DIAGONAL_FIRST || direction == CCG::SCROLL_DIAGONAL_SECOND)
		{
			//Vertical scroll
			if(getPosY() < 0)
			{
				posYCopy += getSizeY();
			}
			else
			{
				posYCopy -= getSizeY();
			}
		}

		SDL_Rect renderBox = {(int)getPosX(), (int)getPosY(), (int)getSizeX(), (int)getSizeY()};
		SDL_RenderCopyEx(renderer, texture->getTexture(), NULL, &renderBox, getRotation(), NULL, SDL_FLIP_NONE);

		if(direction != CCG::SCROLL_OFF)
		{
			//One copy needed in the extended move direction of the original
			SDL_Rect renderBoxCopy = {(int)posXCopy, (int)posYCopy, (int)getSizeX(), (int)getSizeY()};
			SDL_RenderCopyEx(renderer, texture->getTexture(), NULL, &renderBoxCopy, getRotation(), NULL, SDL_FLIP_NONE);
		}

		if(direction == CCG::SCROLL_DIAGONAL_FIRST || direction == CCG::SCROLL_DIAGONAL_SECOND)
		{
			//Three copies needed in the extended move direction of the original, the horizontal and vertical direction
			SDL_Rect renderBoxCopyVertical = {(int)posXCopy, (int)getPosY(), (int)getSizeX(), (int)getSizeY()};
			SDL_RenderCopyEx(renderer, texture->getTexture(), NULL, &renderBoxCopyVertical, getRotation(), NULL, SDL_FLIP_NONE);

			SDL_Rect renderBoxCopyHorizontal = {(int)getPosX(), (int)posYCopy, (int)getSizeX(), (int)getSizeY()};
			SDL_RenderCopyEx(renderer, texture->getTexture(), NULL, &renderBoxCopyHorizontal, getRotation(), NULL, SDL_FLIP_NONE);
		}
	}
}

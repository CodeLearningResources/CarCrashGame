/*
 * SDLTexture.cpp
 *
 *  Created on: 15-mrt.-2015
 *      Author: Thomas
 */

#include "SDLTexture.h"

using namespace CCG_SDL;

SDLTexture::SDLTexture()
{
	texture = NULL;
	textureWidth = 0;
	textureHeight = 0;
}

SDLTexture::SDLTexture(SDL_Texture* texture, int width, int height)
{
	this->texture = texture;
	this->textureWidth = width;
	this->textureHeight = height;
}

SDLTexture::~SDLTexture()
{
	//Deallocate
	free();
}

void SDLTexture::setTexture(SDL_Texture* texture, int width, int height)
{
	//Unload pre-existing texture
	free();

	this->texture = texture;
	this->textureWidth = width;
	this->textureHeight = height;
}

void SDLTexture::free()
{
	//Free texture if existing
	if(texture != NULL)
	{
		SDL_DestroyTexture(texture);
		texture = NULL;
		textureWidth = 0;
		textureHeight = 0;
	}
}

void SDLTexture::setAlphaBlending(bool flag)
{
	if(texture != NULL)
	{
		if(flag)
		{
			SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
		}
		else
		{
			SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_NONE);
		}
	}
}

void SDLTexture::setAlpha(int alpha)
{
	if(texture != NULL)
	{
		SDL_SetTextureAlphaMod(texture, alpha);
	}
}

SDL_Texture* SDLTexture::getTexture() const
{
	return texture;
}

int SDLTexture::getWidth() const
{
	return textureWidth;
}

int SDLTexture::getHeight() const
{
	return textureHeight;
}

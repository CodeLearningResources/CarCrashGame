/*
 * SDLFont.cpp
 *
 *  Created on: 4-apr.-2015
 *      Author: Thomas
 */

#include "SDLFont.h"

using namespace CCG_SDL;

SDLFont::SDLFont()
{
	font = NULL;
}

SDLFont::SDLFont(TTF_Font* font)
{
	this->font = font;
}

SDLFont::~SDLFont()
{
	free();
}

void SDLFont::setFont(TTF_Font* font)
{
	//Unload pre-existing font
	free();

	this->font = font;
}

void SDLFont::free()
{
	//Free font if existing
	if(font != NULL)
	{
		TTF_CloseFont(font);
		font = NULL;
	}
}

TTF_Font* SDLFont::getFont()
{
	return font;
}



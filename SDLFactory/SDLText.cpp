/*
 * SDLText.cpp
 *
 *  Created on: 23-mrt.-2015
 *      Author: Thomas
 */

#include "SDLText.h"

using namespace CCG_SDL;

SDLText::SDLText() : CCG::Text()
{
	visibility = false;
	font = NULL;
	renderer = NULL;
	texture = NULL;
}

SDLText::SDLText(SDL_Renderer* renderer, SDLFont* font, std::string text) : CCG::Text(text)
{
	this->visibility = false;
	this->font = font;
	this->renderer = renderer;
	this->texture = NULL;
	renderText();
}

SDLText::SDLText(const SDLText& text) : CCG::Text(text)
{
	this->visibility = text.visibility;
	this->font = text.font;
	this->renderer = text.renderer;
	this->texture = text.texture;
}

SDLText::~SDLText()
{
	delete(texture);
}

void SDLText::setText(std::string text)
{
	Text::setText(text);

	renderText();
}

void SDLText::setWrapLength(uint32_t wrapLength)
{
	Text::setWrapLength(wrapLength);

	renderText();
}

void SDLText::setColor(uint8_t red, uint8_t green, uint8_t blue, uint8_t opaque)
{
	Text::setColor(red, green, blue, opaque);

	renderText();
}

void SDLText::setFont(SDLFont* font)
{
	this->font = font;
	renderText();
}

SDLFont* SDLText::getFont()
{
	return font;
}

void SDLText::visible(bool flag)
{
	visibility = flag;
}

bool SDLText::isVisible()
{
	return visibility;
}

void SDLText::update()
{
	if(texture == NULL)
	{
		return;
	}

	if(visibility)
	{
		SDL_Rect renderBox = {(int)getPosX(), (int)getPosY(), (int)getSizeX(), (int)getSizeY()};
		SDL_RenderCopyEx(renderer, texture->getTexture(), NULL, &renderBox, (double)getRotation() + getRelRotation(), NULL, SDL_FLIP_NONE);
	}
}

int SDLText::renderText()
{
	std::string text = getText();

	//Free texture if existing
	if(texture != NULL)
	{
		delete(texture);

		texture = NULL;

		setSize(0, 0);
	}

	if(&text != NULL)
	{
		if(strcmp(text.c_str(), "") == 0)
		{
			return 0;	//Text is empty
		}
	}
	else
	{
		return -1;	//Text is NULL (invalid)
	}

	//Text color
	SDL_Color color = {getRed(), getGreen(), getBlue(), getOpaque()};

	if(font == NULL)
	{
		printf("Unable to load font! No font assigned: NULL\n");
		return -1;
	}

	//Render text surface
	SDL_Surface* textSurface = TTF_RenderText_Blended_Wrapped(font->getFont(), getText().c_str(), color, getWrapLength());

	if(textSurface == NULL)
	{
		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
		return -1;
	}
	else
	{
		//Create texture from text surface
		texture = new SDLTexture(SDL_CreateTextureFromSurface(renderer, textSurface), textSurface->w, textSurface->h);

		if(texture == NULL)
		{
			printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
			return -1;
		}
		else
		{
			//Get text dimensions
			setSize(textSurface->w, textSurface->h);
		}

		//Release the old surface
		SDL_FreeSurface(textSurface);
	}

	return 0;
}

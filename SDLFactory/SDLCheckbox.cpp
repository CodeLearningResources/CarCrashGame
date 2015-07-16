/*
 * SDLCheckbox.cpp
 *
 *  Created on: 10-mei-2015
 *      Author: Thomas
 */

#include "SDLCheckbox.h"

using namespace CCG_SDL;

SDLCheckbox::SDLCheckbox()
{
	visibility = false;
	texturePack = new SDLTexture*[CCG::GAMECHECKBOX_MAX]();
	textureCheckTick = NULL;
	renderer = NULL;
}

SDLCheckbox::SDLCheckbox(SDL_Renderer* renderer, SDLTexture** texturePack)
{
	this->visibility = false;
	this->texturePack = new SDLTexture*[CCG::GAMECHECKBOX_MAX]();
	this->textureCheckTick = NULL;
	this->renderer = renderer;

	this->setTexturePack(texturePack);
}

SDLCheckbox::~SDLCheckbox()
{
	delete(texturePack);
}

void SDLCheckbox::setTexturePack(SDLTexture** texturePack)
{
	if(texturePack != NULL)
	{
		this->texturePack[CCG::GAMECHECKBOX_NORMAL] = texturePack[CHECKBOX_ELEMENT_NORMAL];
		this->texturePack[CCG::GAMECHECKBOX_HIGHLIGHTED] = texturePack[CHECKBOX_ELEMENT_HIGHLIGHTED];
		this->textureCheckTick = texturePack[CHECKBOX_ELEMENT_CHECKTICK];
	}
}

SDLTexture** SDLCheckbox::getTexturePack()
{
	return this->texturePack;
}

void SDLCheckbox::visible(bool flag)
{
	this->visibility = flag;
}

bool SDLCheckbox::isVisible(void)
{
	return this->visibility;
}

void SDLCheckbox::update(void)
{
	CCG::GameCheckboxState state = this->getCheckboxState();

	if(texturePack[state] == NULL || textureCheckTick == NULL)
	{
		return;
	}

	if(visibility)
	{
		SDL_Rect renderBox = {(int)getPosX(), (int)getPosY(), (int)getSizeX(), (int)getSizeY()};
		SDL_RenderCopyEx(renderer, texturePack[state]->getTexture(), NULL, &renderBox, getRotation() + getRelRotation(), NULL, SDL_FLIP_NONE);

		if(this->getCheckState())
		{
			SDL_RenderCopyEx(renderer, textureCheckTick->getTexture(), NULL, &renderBox, getRotation() + getRelRotation(), NULL, SDL_FLIP_NONE);
		}
	}
}

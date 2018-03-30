/*
 * SDLButton.cpp
 *
 *  Created on: 15-apr.-2015
 *      Author: Thomas
 */

#include "SDLButton.h"

using namespace CCG_SDL;

SDLButton::SDLButton() : Button()
{
	this->visibility = false;
	this->texturePack = new SDLTexture*[CCG::GAMEBUTTON_MAX]();
	this->renderer = NULL;
	this->clickSound = NULL;
}

SDLButton::SDLButton(SDL_Renderer* renderer, SDLTexture** texturePack, SDLSound* clickSound) : Button()
{
	this->visibility = false;
	this->texturePack = new SDLTexture*[CCG::GAMEBUTTON_MAX]();
	this->renderer = renderer;
	this->clickSound = clickSound;

	setTexturePack(texturePack);
}

//Copy constructor
SDLButton::SDLButton(const SDLButton& button) : CCG::Button()
{
	this->visibility = button.visibility;
	this->texturePack = new SDLTexture*[CCG::GAMEBUTTON_MAX]();
	this->renderer = button.renderer;
	this->clickSound = button.clickSound;

	setTexturePack(button.texturePack);
}

SDLButton::~SDLButton()
{
	delete(texturePack);
}

void SDLButton::setTexturePack(SDLTexture** texturePack)
{
	if(texturePack != NULL)
	{
		this->texturePack[CCG::GAMEBUTTON_NORMAL] = texturePack[CCG::GAMEBUTTON_NORMAL];
		this->texturePack[CCG::GAMEBUTTON_PRESSED] = texturePack[CCG::GAMEBUTTON_PRESSED];
		this->texturePack[CCG::GAMEBUTTON_HIGHLIGHTED] = texturePack[CCG::GAMEBUTTON_HIGHLIGHTED];
		this->texturePack[CCG::GAMEBUTTON_INACTIVE] = texturePack[CCG::GAMEBUTTON_INACTIVE];
	}
}

SDLTexture** SDLButton::getTexturePack()
{
	return this->texturePack;
}

void SDLButton::visible(bool flag)
{
	this->visibility = flag;
}

bool SDLButton::isVisible()
{
	return this->visibility;
}

void SDLButton::update()
{
	CCG::GameButtonState state = this->getButtonState();

	if(texturePack[state] == NULL)
	{
		return;
	}

	if(visibility)
	{
		SDL_Rect renderBox = {(int)getPosX(), (int)getPosY(), (int)getSizeX(), (int)getSizeY()};
		SDL_RenderCopyEx(renderer, texturePack[state]->getTexture(), NULL, &renderBox, getRotation() + getRelRotation(), NULL, SDL_FLIP_NONE);
	}
}

void SDLButton::playClickSound()
{
	if(clickSound != NULL)
	{
		clickSound->playSound();
	}
}

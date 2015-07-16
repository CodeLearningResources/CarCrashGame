/*
 * SDLTextbox.cpp
 *
 *  Created on: 17-apr.-2015
 *      Author: Thomas
 */

#include "SDLTextbox.h"

using namespace CCG_SDL;

SDLTextbox::SDLTextbox() : CCG::Textbox()
{
	this->visibility = false;
	this->texturePack = new SDLTexture*[CCG::TEXTBOX_STATE_MAX]();
	this->textFont = NULL;
	this->renderer = NULL;
}

SDLTextbox::SDLTextbox(SDL_Renderer* renderer, SDLText* textFont, SDLTexture** texturePack) : CCG::Textbox()
{
	this->visibility = false;
	this->texturePack = new SDLTexture*[CCG::TEXTBOX_STATE_MAX]();
	this->textFont = textFont;
	this->renderer = renderer;

	textFont->visible(true);
	setTexturePack(texturePack);
}

SDLTextbox::~SDLTextbox()
{
	delete(texturePack);
}

void SDLTextbox::setText(std::string* text)
{
	CCG::Textbox::setText(text);

	updateText();
}

void SDLTextbox::setTextFont(SDLText* textFont)
{
	if(textFont != NULL)
	{
		delete(textFont);
	}

	this->textFont = textFont;
}

void SDLTextbox::setTexturePack(SDLTexture** texturePack)
{
	if(texturePack != NULL)
	{
		this->texturePack[CCG::TEXTBOX_STATE_NORMAL] = texturePack[CCG::TEXTBOX_STATE_NORMAL];
		this->texturePack[CCG::TEXTBOX_STATE_ACTIVE] = texturePack[CCG::TEXTBOX_STATE_ACTIVE];
		this->texturePack[CCG::TEXTBOX_STATE_HIGHLIGHTED] = texturePack[CCG::TEXTBOX_STATE_HIGHLIGHTED];
	}
}

void SDLTextbox::addCharacter(char character)
{
	CCG::Textbox::addCharacter(character);

	updateText();
}

void SDLTextbox::delCharacter()
{
	CCG::Textbox::delCharacter();

	updateText();
}

SDLText* SDLTextbox::getTextFont()
{
	return this->textFont;
}

SDLTexture** SDLTextbox::getTexturePack()
{
	return this->texturePack;
}

void SDLTextbox::visible(bool flag)
{
	this->visibility = flag;
}

bool SDLTextbox::isVisible()
{
	return this->visibility;
}

void SDLTextbox::update()
{
	CCG::TextboxState state = this->getTextboxState();

	if(texturePack[state] == NULL && textFont == NULL)
	{
		return;
	}

	if(visibility)
	{
		SDL_Rect renderBox = {(int)getPosX(), (int)getPosY(), (int)getSizeX(), (int)getSizeY()};
		SDL_RenderCopyEx(renderer, texturePack[state]->getTexture(), NULL, &renderBox, getRotation() + getRelRotation(), NULL, SDL_FLIP_NONE);

		textFont->setPos(getPosX() + getSizeX()/2 - textFont->getSizeX()/2, getPosY() + getSizeY()/2 - textFont->getSizeY()/2);
		textFont->update();
	}
}

void SDLTextbox::updateText()
{
	if(textFont != NULL)
	{
		textFont->setText(this->getText());
	}
}

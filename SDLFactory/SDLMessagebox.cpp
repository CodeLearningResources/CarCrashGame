/*
 * SDLMessagebox.cpp
 *
 *  Created on: 16-jun.-2015
 *      Author: Thomas
 */

#include "SDLMessagebox.h"

using namespace CCG_SDL;

SDLMessagebox::SDLMessagebox() : Messagebox()
{
	this->visibility = false;
	this->texture = NULL;
	this->button1 = NULL;
	this->button2 = NULL;
	this->messageFont = NULL;
	this->button1Font = NULL;
	this->button2Font = NULL;
	this->renderer = NULL;
}

SDLMessagebox::SDLMessagebox(SDL_Renderer* renderer, SDLTexture* texture, SDLButton* button, SDLText* messageFont, SDLText* buttonFont, std::string* messageText, std::string* buttonText1, std::string* buttonText2) : CCG::Messagebox(messageText, buttonText1, buttonText2)
{
	this->visibility = false;
	this->texture = texture;
	this->button1 = button;
	this->button2 = new SDLButton(*button);
	this->messageFont = messageFont;
	this->button1Font = buttonFont;
	this->button2Font = new SDLText(*buttonFont);
	this->renderer = renderer;

	this->visible(false);
	this->updateProportions();
}

SDLMessagebox::~SDLMessagebox()
{
	delete(button1);
	button1 = NULL;

	delete(button2);
	button2 = NULL;

	delete(messageFont);
	messageFont = NULL;

	delete(button1Font);
	button1Font = NULL;

	delete(button2Font);
	button2Font = NULL;
}

void SDLMessagebox::setBackgroundTexture(SDLTexture* texture)
{
	this->texture = texture;
}

SDLTexture* SDLMessagebox::getBackgroundTexture()
{
	return this->texture;
}

void SDLMessagebox::visible(bool flag)
{
	this->visibility = flag;
	this->messageFont->visible(flag);
	this->button1Font->visible(flag);
	this->button2Font->visible(flag);
	this->button1->visible(flag);
	this->button2->visible(flag);
}

bool SDLMessagebox::isVisible()
{
	return this->visibility;
}

void SDLMessagebox::update()
{
	if(texture == NULL)
	{
		return;
	}

	if(visibility)
	{
		SDL_Rect renderBox = {(int)getPosX(), (int)getPosY(), (int)getSizeX(), (int)getSizeY()};
		SDL_RenderCopyEx(renderer, texture->getTexture(), NULL, &renderBox, getRotation() + getRelRotation(), NULL, SDL_FLIP_NONE);

		this->messageFont->update();

		if(this->displayedButtons > 0)
		{
			this->button1->update();
			this->button1Font->update();
		}

		if(this->displayedButtons > 1)
		{
			this->button2->update();
			this->button2Font->update();
		}
	}
}

void SDLMessagebox::setMessageText(std::string* text)
{
	CCG::Messagebox::setMessageText(text);

	if(this->messageFont != NULL)
	{
		this->messageFont->setText(*text);
	}

	this->updateProportions();
}

void SDLMessagebox::setButtons(std::string* buttonText1, std::string* buttonText2)
{
	CCG::Messagebox::setButtons(buttonText1, buttonText2);

	this->updateProportions();
}

void SDLMessagebox::updateProportions(void)
{
	uint32_t wrapLength;
	float posX, posY = 0.0f;

	//Set message
	if(this->getSizeX() < 30)
	{
		wrapLength = (uint32_t)this->getSizeX();
	}
	else
	{
		wrapLength = (uint32_t)this->getSizeX() - 30;
	}

	this->messageFont->setWrapLength(wrapLength);
	this->messageFont->setPos(this->getPosX() + this->getSizeX()/2 - this->messageFont->getSizeX()/2, this->getPosY() + 15);

	//Set buttons
	if(this->displayedButtons == 1)
	{
		//Set button size and position
		this->button1->setSize(this->getSizeX()/2, this->getSizeY()/5);

		posX = this->getPosX() + this->getSizeX()/2 - this->button1->getSizeX()/2;
		posY = this->getPosY() + this->getSizeY() - 15 - this->button1->getSizeY();

		this->button1->setPos(posX, posY);

		//Set buttontext position
		this->button1Font->setText(this->getButtonText1()->c_str());

		posX = this->button1->getPosX() + this->button1->getSizeX()/2 - this->button1Font->getSizeX()/2;
		posY = this->button1->getPosY() + this->button1->getSizeY()/2 - this->button1Font->getSizeY()/2;

		this->button1Font->setPos(posX, posY);
	}
	else if(this->displayedButtons == 2)
	{
		//Set buttons size and position
		this->button1->setSize(this->getSizeX()/3, this->getSizeY()/5);
		this->button2->setSize(this->getSizeX()/3, this->getSizeY()/5);

		//Button 1 (Left)
		posX = this->getPosX() + this->getSizeX()/3 - 5 - this->button1->getSizeX()/2;
		posY = this->getPosY() + this->getSizeY() - 15 - this->button1->getSizeY();

		this->button1->setPos(posX, posY);

		//Button 2 (Right)
		posX = this->getPosX() + this->getSizeX()/3 + 5 + this->button1->getSizeX()/2;

		this->button2->setPos(posX, posY);

		//Set buttontexts position
		this->button1Font->setText(this->getButtonText1()->c_str());
		this->button2Font->setText(this->getButtonText2()->c_str());

		posX = this->button1->getPosX() + this->button1->getSizeX()/2 - this->button1Font->getSizeX()/2;
		posY = this->button1->getPosY() + this->button1->getSizeY()/2 - this->button1Font->getSizeY()/2;

		this->button1Font->setPos(posX, posY);

		posX = this->button2->getPosX() + this->button2->getSizeX()/2 - this->button2Font->getSizeX()/2;
		posY = this->button2->getPosY() + this->button2->getSizeY()/2 - this->button2Font->getSizeY()/2;

		this->button2Font->setPos(posX, posY);
	}
}

int SDLMessagebox::checkMessageboxState(int posX, int posY, bool pressed)
{
	int buttonState = 0;

	if(this->displayedButtons == 1)
	{
		buttonState = this->button1->checkButtonState(posX, posY, pressed);
	}
	else if(this->displayedButtons == 2)
	{
		buttonState = this->button1->checkButtonState(posX, posY, pressed) + 2*(this->button2->checkButtonState(posX, posY, pressed));
	}

	return buttonState;
}

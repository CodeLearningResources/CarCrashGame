/*
 * Messagebox.cpp
 *
 *  Created on: 16-jun.-2015
 *      Author: Thomas
 */

#include "Messagebox.h"

using namespace CCG;

Messagebox::Messagebox()
{
	messageText = "";
	buttonText1 = "";
	buttonText2 = "";
	displayedButtons = 0;
}

Messagebox::Messagebox(std::string* messageText, std::string* buttonText1, std::string* buttonText2)
{
	this->displayedButtons = 0;
	this->messageText = "";
	this->buttonText1 = "";
	this->buttonText2 = "";

	this->setMessageText(messageText);

	this->setButtons(buttonText1, buttonText2);
}

Messagebox::~Messagebox()
{

}

void Messagebox::setMessageText(std::string* text)
{
	if(text != NULL)
	{
		this->messageText = *text;
	}
}

void Messagebox::setButtons(std::string* buttonText1, std::string* buttonText2)
{
	this->displayedButtons = 0;

	if(buttonText1 != NULL)
	{
		this->buttonText1 = *buttonText1;
		this->displayedButtons++;

		if(buttonText2 != NULL)
		{
			this->buttonText2 = *buttonText2;
			this->displayedButtons++;
		}
	}
}

std::string* Messagebox::getMessageText(void)
{
	return &this->messageText;
}

std::string* Messagebox::getButtonText1(void)
{
	if(this->displayedButtons >= 1)
	{
		return &this->buttonText1;
	}
	else
	{
		return NULL;
	}
}

std::string* Messagebox::getButtonText2(void)
{
	if(this->displayedButtons >= 2)
	{
		return &this->buttonText2;
	}
	else
	{
		return NULL;
	}
}

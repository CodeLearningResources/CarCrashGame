/*
 * Textbox.cpp
 *
 *  Created on: 17-apr.-2015
 *      Author: Thomas
 */

#include "Textbox.h"

using namespace CCG;

Textbox::Textbox() : GameElement()
{
	limit = 13;
	text = "";
	state = TEXTBOX_STATE_NORMAL;
}

Textbox::Textbox(const Textbox& textbox) : GameElement(textbox)
{
	this->limit = textbox.limit;
	this->text = textbox.text;
	this->state = textbox.state;
}

Textbox::~Textbox()
{

}

void Textbox::setCharactersLimit(int limit)
{
	this->limit = limit;
}

void Textbox::setText(std::string* text)
{
	this->text = *text;
}

void Textbox::setFocus(bool flag)
{
	if(flag)
	{
		this->state = TEXTBOX_STATE_ACTIVE;
	}
	else
	{
		this->state = TEXTBOX_STATE_NORMAL;
	}
}

int Textbox::getCharactersLimit() const
{
	return this->limit;
}

std::string Textbox::getText() const
{
	return this->text;
}

TextboxState Textbox::getTextboxState() const
{
	return this->state;
}

void Textbox::checkFocusState(int posX, int posY, bool selected)
{
	if(checkIntersection(posX, posY))
	{
		if(selected)
		{
			this->state = TEXTBOX_STATE_ACTIVE;
		}
		else if(getTextboxState() != TEXTBOX_STATE_ACTIVE)
		{
			this->state = TEXTBOX_STATE_HIGHLIGHTED;
		}
	}
	else
	{
		if(selected || getTextboxState() != TEXTBOX_STATE_ACTIVE)
		{
			this->state = TEXTBOX_STATE_NORMAL;
		}
	}
}

void Textbox::addCharacter(char character)
{
	if(text.size() < (unsigned)limit)
	{
		text.push_back(character);
	}
}

void Textbox::delCharacter()
{
	if(text.size() > 0)
	{
		text = text.substr(0, text.size() - 1);
	}
}

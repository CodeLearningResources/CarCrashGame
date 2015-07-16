/*
 * Button.cpp
 *
 *  Created on: 15-apr.-2015
 *      Author: Thomas
 */

#include "Button.h"

using namespace CCG;

Button::Button() : GameElement()
{
	inactive = false;
	state = GAMEBUTTON_NORMAL;
}

Button::Button(const Button& button) : GameElement(button)
{
	this->inactive = button.inactive;
	this->state = button.state;
}

Button::~Button()
{

}

void Button::setInactive(bool flag)
{
	this->inactive = flag;

	if(flag)
	{
		this->setButtonState(GAMEBUTTON_INACTIVE);
	}
	else
	{
		this->setButtonState(GAMEBUTTON_NORMAL);
	}
}

void Button::setButtonState(GameButtonState state)
{
	if(state != GAMEBUTTON_MAX)
	{
		this->state = state;
	}
}

bool Button::getInactiveState() const
{
	return this->inactive;
}

GameButtonState Button::getButtonState() const
{
	return this->state;
}

bool Button::checkButtonState(int posX, int posY, bool pressed)
{
	bool clicked = false;

	if(this->inactive)
	{
		setButtonState(GAMEBUTTON_INACTIVE);
	}
	else if(checkIntersection(posX, posY))
	{
		if(pressed)
		{
			setButtonState(GAMEBUTTON_PRESSED);
		}
		else
		{
			//Check if previous state the button was pressed
			if(state == GAMEBUTTON_PRESSED)
			{
				clicked = true;
			}

			setButtonState(GAMEBUTTON_HIGHLIGHTED);
		}
	}
	else
	{
		setButtonState(GAMEBUTTON_NORMAL);
	}

	return clicked;
}

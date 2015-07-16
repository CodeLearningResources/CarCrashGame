/*
 * Checkbox.cpp
 *
 *  Created on: 10-mei-2015
 *      Author: Thomas
 */

#include "Checkbox.h"

using namespace CCG;

Checkbox::Checkbox() : GameElement()
{
	inactive = false;
	checked = false;
	state = GAMECHECKBOX_NORMAL;
}

Checkbox::Checkbox(bool checked) : GameElement()
{
	this->inactive = false;
	this->checked = checked;
	this->state = GAMECHECKBOX_NORMAL;
}

Checkbox::Checkbox(const Checkbox& checkbox) : GameElement(checkbox)
{
	this->inactive = checkbox.inactive;
	this->checked = checkbox.checked;
	this->state = checkbox.state;
}

Checkbox::~Checkbox()
{

}

void Checkbox::setChecked(bool checked)
{
	this->checked = checked;
}

void Checkbox::setInactive(bool flag)
{
	this->inactive = flag;
}

bool Checkbox::getCheckState() const
{
	return this->checked;
}

bool Checkbox::getInactiveState() const
{
	return this->inactive;
}

GameCheckboxState Checkbox::getCheckboxState(void) const
{
	return this->state;
}


bool Checkbox::checkCheckboxState(int posX, int posY, bool pressed)
{
	bool changed = false;

	if(!this->inactive && checkIntersection(posX, posY))
	{
		if(pressed)
		{
			this->checked = !this->checked;

			changed = true;
		}

		this->state = GAMECHECKBOX_HIGHLIGHTED;
	}
	else
	{
		this->state = GAMECHECKBOX_NORMAL;
	}

	return changed;
}

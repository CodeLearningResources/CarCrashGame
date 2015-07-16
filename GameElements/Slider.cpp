/*
 * Slider.cpp
 *
 *  Created on: 27-apr.-2015
 *      Author: Thomas
 */

#include "Slider.h"

using namespace CCG;

Slider::Slider() : GameElement()
{
	value = 0;
	inactive = false;
}

Slider::Slider(int value) : GameElement()
{
	this->value = value;
	this->inactive = false;
}

Slider::Slider(const Slider& slider) : GameElement(slider)
{
	this->value = slider.value;
	this->inactive = slider.inactive;
}

Slider::~Slider()
{

}

void Slider::setValue(int value)
{
	this->value = value;
}

void Slider::setInactive(bool flag)
{
	this->inactive = flag;
}

int Slider::getValue() const
{
	return this->value;
}

bool Slider::getInactiveState() const
{
	return this->inactive;
}

bool Slider::checkSliderState(int posX, int posY, bool pressed)
{
	bool changed = false;

	if(!this->inactive && checkIntersection(posX, posY))
	{
		if(pressed)
		{
			int markerSizeCorrection = getSizeY() / 2;		//Marker ratio W:H = 1:2
			int sliderValue = ((posX - getPosX() - (markerSizeCorrection / 2)) / (getSizeX() - markerSizeCorrection)) * 100;

			if(sliderValue < 0)
			{
				sliderValue = 0;
			}

			if(sliderValue > 100)
			{
				sliderValue = 100;
			}

			this->setValue(sliderValue);

			changed = true;
		}
	}

	return changed;
}

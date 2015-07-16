/*
 * Text.cpp
 *
 *  Created on: 23-mrt.-2015
 *      Author: Thomas
 */

#include "Text.h"

using namespace CCG;

Text::Text() : GameElement()
{
	text = "";
	red = 0;
	green = 0;
	blue = 0;
	opaque = 0;
	wrapLength = 0;		//No wrapping
}

Text::Text(std::string text) : GameElement()
{
	this->text = text;
	red = 0;
	green = 0;
	blue = 0;
	opaque = 0;
	wrapLength = 0;		//No wrapping
}

Text::Text(const Text& text) : GameElement(text)
{
	this->text = text.text;
	this->red = text.red;
	this->green = text.green;
	this->blue = text.blue;
	this->opaque = text.opaque;
	this->wrapLength = text.opaque;
}

Text::~Text()
{

}

void Text::setText(std::string text)
{
	this->text = text;
}

void Text::setWrapLength(uint32_t wrapLength)
{
	this->wrapLength = wrapLength;
}

void Text::setColor(uint8_t red, uint8_t green, uint8_t blue, uint8_t opaque)
{
	this->red = red;
	this->green = green;
	this->blue = blue;
	this->opaque = opaque;
}

std::string Text::getText() const
{
	return text;
}

uint32_t Text::getWrapLength() const
{
	return wrapLength;
}

uint8_t Text::getRed() const
{
	return red;
}

uint8_t Text::getGreen() const
{
	return green;
}

uint8_t Text::getBlue() const
{
	return blue;
}

uint8_t Text::getOpaque() const
{
	return opaque;
}

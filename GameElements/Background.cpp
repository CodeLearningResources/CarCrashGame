/*
 * Background.cpp
 *
 *  Created on: 22-mrt.-2015
 *      Author: Thomas
 */

#include "Background.h"

using namespace CCG;

Background::Background() : GameElement()
{
	direction = SCROLL_OFF;
}

Background::Background(ScrollDirection direction) : GameElement()
{
	this->direction = direction;
}

Background::Background(const Background& background) : GameElement(background)
{
	this->direction = direction;
}

Background::~Background()
{

}

void Background::setSpeed(float speed)
{
	if(direction == SCROLL_HORIZONTAL)
	{
		setVelX(speed);
	}
	else if(direction == SCROLL_VERTICAL)
	{
		setVelY(speed);
	}
	else if(direction == SCROLL_DIAGONAL_FIRST)
	{
		setVelX(speed);
		setVelY(speed);
	}
	else if(direction == SCROLL_DIAGONAL_SECOND)
	{
		setVelX(-speed);
		setVelY(speed);
	}
}

ScrollDirection Background::getScrollDirection() const
{
	return direction;
}

float Background::getSpeed() const
{
	if(direction == SCROLL_HORIZONTAL)
	{
		return getVelX();
	}
	else if(direction == SCROLL_VERTICAL)
	{
		return getVelY();
	}
	else if(direction == SCROLL_DIAGONAL_FIRST)
	{
		return getVelX();
	}
	else if(direction == SCROLL_DIAGONAL_SECOND)
	{
		return getVelY();
	}
	else
	{
		return 0;
	}
}

void Background::move(float timeStep)
{
	float pos = 0;
	float vel = 0;

	if(direction == SCROLL_HORIZONTAL || direction == SCROLL_DIAGONAL_FIRST || direction == SCROLL_DIAGONAL_SECOND)
	{
		pos = getPosX();
		vel = getVelX();

		pos += vel * timeStep;
		if(pos <= -getSizeX() || pos >= getSizeX())
		{
			pos = 0;
		}

		setPosX(pos);
	}

	if(direction == SCROLL_VERTICAL || direction == SCROLL_DIAGONAL_FIRST || direction == SCROLL_DIAGONAL_SECOND)
	{
		pos = getPosY();
		vel = getVelY();

		pos += vel * timeStep;
		if(pos <= -getSizeY() || pos >= getSizeY())
		{
			pos = 0;
		}

		setPosY(pos);
	}
}

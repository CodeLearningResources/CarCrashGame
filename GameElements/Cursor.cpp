/*
 * Cursor.cpp
 *
 *  Created on: 19-jun.-2015
 *      Author: Thomas
 */

#include "Cursor.h"

using namespace CCG;

Cursor::Cursor() : GameElement()
{
	state = CURSOR_STATE_NORMAL;
	setSize(30, 30);
}

Cursor::Cursor(const Cursor& cursor) : GameElement(cursor)
{
	this->state = cursor.state;
}

Cursor::~Cursor()
{

}

void Cursor::setCursorPosition(int posX, int posY, bool clicking)
{
	this->setPos(posX, posY);

	if(clicking)
	{
		this->state = CURSOR_STATE_CLICK;
	}
	else
	{
		this->state = CURSOR_STATE_NORMAL;
	}
}

CursorState Cursor::getCursorState()
{
	return this->state;
}

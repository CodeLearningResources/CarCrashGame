/*
 * SDLMouseEvent.cpp
 *
 *  Created on: 29-mrt.-2015
 *      Author: Thomas
 */

#include "SDLMouseEvent.h"

using namespace CCG_SDL;

SDLMouseEvent::SDLMouseEvent() : SDLEvent(CCG::MOUSE_EVENT)
{

}

SDLMouseEvent::SDLMouseEvent(SDL_Event* event) : SDLEvent(CCG::MOUSE_EVENT)
{
	int mousePosX = 0;
	int mousePosY = 0;
	int buttonState = 0;
	CCG::ButtonState lState = CCG::BUTTON_UNPRESSED;
	CCG::ButtonState rState = CCG::BUTTON_UNPRESSED;

	//Get mouse state
	buttonState = SDL_GetMouseState(&mousePosX, &mousePosY);

	this->setMousePosition(mousePosX, mousePosY);

	if(buttonState & SDL_BUTTON(SDL_BUTTON_LEFT))
	{
		lState = CCG::BUTTON_PRESSED;
	}

	if(buttonState & SDL_BUTTON(SDL_BUTTON_RIGHT))
	{
		rState = CCG::BUTTON_PRESSED;
	}

	this->setMouseButtonState(lState, rState);
}

SDLMouseEvent::~SDLMouseEvent()
{

}

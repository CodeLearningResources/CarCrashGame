/*
 * SDLEventStack.cpp
 *
 *  Created on: 28-mrt.-2015
 *      Author: Thomas
 */

#include "SDLEventStack.h"

using namespace CCG_SDL;

SDLEventStack::SDLEventStack() : CCG::EventStack()
{

}

SDLEventStack::~SDLEventStack()
{

}

CCG::Event* SDLEventStack::pollEvent()
{
	CCG::Event* event = NULL;
	SDL_Event newEvent;

	if(SDL_PollEvent(&newEvent) != 0)
	{
		switch(newEvent.type)
		{
			case SDL_QUIT:
				event = new SDLEvent(CCG::GAME_QUIT);
				break;
			case SDL_KEYDOWN:			//Fall-through for keyboard event
			case SDL_KEYUP:
				event = new SDLKeyboardEvent(&newEvent);
				break;
			case SDL_MOUSEMOTION:		//Fall-through for mouse event
			case SDL_MOUSEBUTTONDOWN:
			case SDL_MOUSEBUTTONUP:
				event = new SDLMouseEvent(&newEvent);
				break;
			default:
				event = new SDLEvent(CCG::UNDEFINED_EVENT);
				break;
		}
		return event;
	}
	else
	{
		return 0;
	}
}

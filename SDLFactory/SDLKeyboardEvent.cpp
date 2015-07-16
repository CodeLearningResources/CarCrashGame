/*
 * SDLKeyboardEvent.cpp
 *
 *  Created on: 18-mrt.-2015
 *      Author: Thomas
 */

#include "SDLKeyboardEvent.h"

using namespace CCG_SDL;

SDLKeyboardEvent::SDLKeyboardEvent() : SDLEvent(CCG::KEYBOARD_EVENT)
{

}

SDLKeyboardEvent::SDLKeyboardEvent(SDL_Event* event) : SDLEvent(CCG::KEYBOARD_EVENT)
{
	int key = (int) event->key.keysym.sym;
	int state = (int) event->key.state;

	if(key >= SDLK_a && key <= SDLK_z)				//Letter key action
	{
		this->setKeyboardKey((CCG::KeyboardValue) (CCG::KEY_A + key - SDLK_a));
	}
	else if(key >= SDLK_0 && key <= SDLK_9)			//Number key action
	{
		this->setKeyboardKey((CCG::KeyboardValue) (CCG::KEY_0 + key - SDLK_0));
	}
	else if(key == SDLK_LEFT)						//Arrow key action: LEFT
	{
		this->setKeyboardKey(CCG::KEY_LEFT);
	}
	else if(key == SDLK_RIGHT)						//Arrow key action: RIGHT
	{
		this->setKeyboardKey(CCG::KEY_RIGHT);
	}
	else if(key == SDLK_UP)							//Arrow key action: UP
	{
		this->setKeyboardKey(CCG::KEY_UP);
	}
	else if(key == SDLK_DOWN)						//Arrow key action: DOWN
	{
		this->setKeyboardKey(CCG::KEY_DOWN);
	}
	else if(key == SDLK_SPACE)						//Spacebar key action
	{
		this->setKeyboardKey(CCG::KEY_SPACE);
	}
	else if(key == SDLK_TAB)						//Tab key action
	{
		this->setKeyboardKey(CCG::KEY_TAB);
	}
	else if(key == SDLK_ESCAPE)						//ESC key action
	{
		this->setKeyboardKey(CCG::KEY_ESCAPE);
	}
	else if(key == SDLK_BACKSPACE)					//Backspace key action
	{
		this->setKeyboardKey(CCG::KEY_BACKSPACE);
	}
	else if(key == SDLK_RETURN)						//Enter key action
	{
		this->setKeyboardKey(CCG::KEY_ENTER);
	}
	else if(key == SDLK_DELETE)						//Delete key action
	{
		this->setKeyboardKey(CCG::KEY_DELETE);
	}
	else if(key == SDLK_INSERT)						//Insert key action
	{
		this->setKeyboardKey(CCG::KEY_INSERT);
	}
	else if(key >= SDLK_F1 && key <= SDLK_F12)		//Function key action: F1 - F12
	{
		this->setKeyboardKey((CCG::KeyboardValue) (CCG::KEY_F1 + key - SDLK_F1));
	}
	else if(key >= SDLK_KP_1 && key <= SDLK_KP_9)	//Keypad number key action: 1 - 9
	{
		this->setKeyboardKey((CCG::KeyboardValue) (CCG::KEY_KEYPAD1 + key - SDLK_KP_1));
	}
	else if(key == SDLK_KP_0)
	{
		this->setKeyboardKey(CCG::KEY_KEYPAD0);
	}
	else											//Key undefined
	{
		this->setKeyboardKey(CCG::KEY_UNDEFINED);
	}
	this->setButtonState((CCG::ButtonState) state);
}

SDLKeyboardEvent::~SDLKeyboardEvent()
{

}

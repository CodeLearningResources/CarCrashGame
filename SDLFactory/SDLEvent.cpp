/*
 * SDLEvent.cpp
 *
 *  Created on: 19-mrt.-2015
 *      Author: Thomas
 */

#include "SDLEvent.h"

using namespace CCG_SDL;

SDLEvent::SDLEvent() : CCG::Event()
{
	this->event = CCG::UNDEFINED_EVENT;
	this->key = new CCG::KeyboardKey(CCG::KEY_UNDEFINED);
	this->state = CCG::UNDEFINED_STATE;
	this->mouseX = 0;
	this->mouseY = 0;
	this->lMouseButtonState = CCG::UNDEFINED_STATE;
	this->rMouseButtonState = CCG::UNDEFINED_STATE;
}

SDLEvent::SDLEvent(CCG::SystemEvent event) : CCG::Event()
{
	this->event = event;
	this->key = new CCG::KeyboardKey(CCG::KEY_UNDEFINED);
	this->state = CCG::UNDEFINED_STATE;
	this->mouseX = 0;
	this->mouseY = 0;
	this->lMouseButtonState = CCG::UNDEFINED_STATE;
	this->rMouseButtonState = CCG::UNDEFINED_STATE;
}

SDLEvent::~SDLEvent()
{
	delete(key);
	key = NULL;
}

CCG::SystemEvent SDLEvent::getType() const
{
	return this->event;
}

CCG::KeyboardKey* SDLEvent::getKeyEvent() const
{
	return this->key;
}

CCG::ButtonState SDLEvent::getButtonState() const
{
	return this->state;
}

void SDLEvent::getMousePosition(int* x, int* y)
{
	*x = this->mouseX;
	*y = this->mouseY;
}

CCG::ButtonState SDLEvent::getLMouseButtonState() const
{
	return this->lMouseButtonState;
}

CCG::ButtonState SDLEvent::getRMouseButtonState() const
{
	return this->rMouseButtonState;
}

void SDLEvent::setKeyboardKey(CCG::KeyboardValue key)
{
	this->key->setKeyValue(key);
}

void SDLEvent::setButtonState(CCG::ButtonState state)
{
	this->state = state;
}

void SDLEvent::setMousePosition(int x, int y)
{
	this->mouseX = x;
	this->mouseY = y;
}

void SDLEvent::setMouseButtonState(CCG::ButtonState lState, CCG::ButtonState rState)
{
	this->lMouseButtonState = lState;
	this->rMouseButtonState = rState;
}

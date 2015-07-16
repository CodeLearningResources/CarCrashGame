/*
 * Event.h
 *
 *  Created on: 18-mrt.-2015
 *      Author: Thomas
 */

#ifndef GAME_EVENT_H_
#define GAME_EVENT_H_

#include "KeyboardKey.h"

namespace CCG
{
	//Events constants
	enum SystemEvent
	{
		UNDEFINED_EVENT,
		GAME_QUIT,
		KEYBOARD_EVENT,
		MOUSE_EVENT
	};

	//State of a button
	enum ButtonState
	{
		UNDEFINED_STATE = -1,
		BUTTON_UNPRESSED,
		BUTTON_PRESSED
	};

	/*
	 * Abstract class for events
	 */
	class Event
	{
		public:
			virtual ~Event(void);

			/**
			 * Get the type of event which it contains
			 * @return Type of event it contains
			 */
			virtual SystemEvent getType(void) const = 0;

			/*
			 * Get the key event if type is a KEYBOARD_EVENT
			 * @return The keyboard key the event contains
			 */
			virtual KeyboardKey* getKeyEvent(void) const = 0;

			/*
			 * Get the state of the button if type is a KEYBOARD_EVENT
			 * @return The state of the button of the keyboard key
			 */
			virtual ButtonState getButtonState(void) const = 0;

			/*
			 * Get the position of the cursor if type is a MOUSE_EVENT
			 * @param x Pointer for the X-position of the cursor location
			 * @param y Pointer for the Y-position of the cursor location
			 */
			virtual void getMousePosition(int* x, int* y) = 0;

			/*
			 * Get the state of the left mouse button if type is a MOUSE_EVENT
			 * @return The state of the button of the left mouse button
			 */
			virtual ButtonState getLMouseButtonState(void) const = 0;

			/*
			 * Get the state of the right mouse button if type is a MOUSE_EVENT
			 * @return The state of the button of the right mouse button
			 */
			virtual ButtonState getRMouseButtonState(void) const = 0;

		protected:
			Event(void);
	};
}

#endif /* GAME_EVENT_H_ */

/*
 * SDLEvent.h
 *
 *  Created on: 19-mrt.-2015
 *      Author: Thomas
 */

#ifndef SDLENGINE_SDLEVENT_H_
#define SDLENGINE_SDLEVENT_H_

#include <SDL2/SDL.h>

#include "../Game/Event.h"

namespace CCG_SDL
{
	/*
	 * SDL implementation of the event class
	 */
	class SDLEvent : public CCG::Event
	{
		public:
			SDLEvent(void);
			SDLEvent(CCG::SystemEvent event);
			~SDLEvent(void);

			CCG::SystemEvent getType(void) const;
			CCG::KeyboardKey* getKeyEvent(void) const;
			CCG::ButtonState getButtonState(void) const;
			void getMousePosition(int* x, int* y);
			CCG::ButtonState getLMouseButtonState(void) const;
			CCG::ButtonState getRMouseButtonState(void) const;

			void setKeyboardKey(CCG::KeyboardValue key);
			void setButtonState(CCG::ButtonState state);
			void setMousePosition(int x, int y);
			void setMouseButtonState(CCG::ButtonState lState, CCG::ButtonState rState);

		private:
			CCG::SystemEvent event;
			CCG::KeyboardKey* key;
			CCG::ButtonState state;
			int mouseX;
			int mouseY;
			CCG::ButtonState lMouseButtonState;
			CCG::ButtonState rMouseButtonState;
	};
}

#endif /* SDLENGINE_SDLEVENT_H_ */

/*
 * SDLKeyboardEvent.h
 *
 *  Created on: 18-mrt.-2015
 *      Author: Thomas
 */

#ifndef SDLENGINE_SDLKEYBOARDEVENT_H_
#define SDLENGINE_SDLKEYBOARDEVENT_H_

#include <SDL2/SDL.h>

#include "SDLEvent.h"

namespace CCG_SDL
{
	/*
	 * SDL event for keyboard events
	 */
	class SDLKeyboardEvent : public SDLEvent
	{
		public:
			SDLKeyboardEvent(void);
			SDLKeyboardEvent(SDL_Event* event);
			~SDLKeyboardEvent(void);
	};
}

#endif /* SDLENGINE_SDLKEYBOARDEVENT_H_ */

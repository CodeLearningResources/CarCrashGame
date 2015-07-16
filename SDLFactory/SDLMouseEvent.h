/*
 * SDLMouseEvent.h
 *
 *  Created on: 29-mrt.-2015
 *      Author: Thomas
 */

#ifndef SDLFACTORY_SDLMOUSEEVENT_H_
#define SDLFACTORY_SDLMOUSEEVENT_H_

#include <SDL2/SDL.h>

#include "SDLEvent.h"

namespace CCG_SDL
{
	/*
	 * SDL event for mouse events
	 */
	class SDLMouseEvent : public SDLEvent
	{
		public:
			SDLMouseEvent(void);
			SDLMouseEvent(SDL_Event* event);
			~SDLMouseEvent(void);
	};
}

#endif /* SDLFACTORY_SDLMOUSEEVENT_H_ */

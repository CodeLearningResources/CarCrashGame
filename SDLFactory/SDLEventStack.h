/*
 * SDLEventStack.h
 *
 *  Created on: 28-mrt.-2015
 *      Author: Thomas
 */

#ifndef SDLFACTORY_SDLEVENTSTACK_H_
#define SDLFACTORY_SDLEVENTSTACK_H_

#include <stdio.h>
#include <SDL2/SDL.h>

#include "../Game/EventStack.h"
#include "SDLEvent.h"
#include "SDLKeyboardEvent.h"
#include "SDLMouseEvent.h"

namespace CCG_SDL
{
	/*
	 * SDL implementation of the event stack class
	 */
	class SDLEventStack : public CCG::EventStack
	{
		public:
			SDLEventStack(void);
			~SDLEventStack(void);

			CCG::Event* pollEvent();
	};
}

#endif /* SDLFACTORY_SDLEVENTSTACK_H_ */

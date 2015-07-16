/*
 * SDLTimer.h
 *
 *  Created on: 23-mrt.-2015
 *      Author: Thomas
 */

#ifndef SDLENGINE_SDLTIMER_H_
#define SDLENGINE_SDLTIMER_H_

#include <SDL2/SDL.h>

#include "../Game/Timer.h"

namespace CCG_SDL
{
	/*
	 * SDL implementation of the timer class
	 */
	class SDLTimer : public CCG::Timer
	{
		public:
			SDLTimer(void);
			~SDLTimer(void);

			//Operations of the timer
			void start(void);
			void stop(void);
			void reset(void);
			void pause(void);
			void unpause(void);

			//Get the number of ticks from the start of the timer
			uint32_t getTicks(void) const;

			//The status of the timer
			bool isStarted(void);
			bool isPaused(void);

		private:
			//Time when the timer started
			Uint32 startTime;

			//Number of ticks when the timer was paused
			Uint32 pausedTime;

			//Timer status
			bool startStatus;
			bool pauseStatus;
	};
}

#endif /* SDLENGINE_SDLTIMER_H_ */

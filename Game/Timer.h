/*
 * Timer.h
 *
 *  Created on: 23-mrt.-2015
 *      Author: Thomas
 */

#ifndef GAME_TIMER_H_
#define GAME_TIMER_H_

#include <stdint.h>

namespace CCG
{
	/*
	 * Abstract timer class
	 */
	class Timer
	{
		public:
			virtual ~Timer(void);

			//Operations of the timer
			virtual void start(void) = 0;
			virtual void stop(void) = 0;
			virtual void reset(void) = 0;
			virtual void pause(void) = 0;
			virtual void unpause(void) = 0;

			//Get the number of ticks from the start of the timer
			virtual uint32_t getTicks(void) const = 0;

			//The status of the timer
			virtual bool isStarted(void) = 0;
			virtual bool isPaused(void) = 0;

		protected:
			Timer(void);
	};
}

#endif /* GAME_TIMER_H_ */

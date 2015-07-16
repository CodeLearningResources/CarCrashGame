/*
 * EventStack.h
 *
 *  Created on: 28-mrt.-2015
 *      Author: Thomas
 */

#ifndef GAME_EVENTSTACK_H_
#define GAME_EVENTSTACK_H_

#include "Event.h"

namespace CCG
{
	/*
	 * Abstract class for the event stack
	 */
	class EventStack
	{
		public:
			virtual ~EventStack(void);

			/*
			 * Get the next event in the queue if available
			 * @return The next event of the queue, NULL if empty
			 */
			virtual Event* pollEvent() = 0;

		protected:
			EventStack(void);
	};
}

#endif /* GAME_EVENTSTACK_H_ */

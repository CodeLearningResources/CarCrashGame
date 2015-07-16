/*
 * Levels.h
 *
 *  Created on: 6-apr.-2015
 *      Author: Thomas
 */

#ifndef LEVELS_LEVELS_H_
#define LEVELS_LEVELS_H_

#include "Level01.h"
#include "Level02.h"

namespace CCG
{
	#define LEVELS_MAX 2

	/*
	 * Collection base of all levels
	 */
	class Levels
	{
		public:
			Levels(void);
			virtual ~Levels(void);

			Level* getLevel(int level);
			int availableLevels(void);

		private:
			Level** levels;

			void initializeLevels(void);
			void releaseLevels(void);
	};
}

#endif /* LEVELS_LEVELS_H_ */

/*
 * Level01.h
 *
 *  Created on: 6-apr.-2015
 *      Author: Thomas
 */

#ifndef LEVELS_LEVEL01_H_
#define LEVELS_LEVEL01_H_

#include "../Game/Level.h"

namespace CCG
{
	/*
	 * Level class
	 */
	class Level01 : public Level
	{
		public:
			Level01(void);
			Level01(const Level& level);
			~Level01(void);
	};
}

#endif /* LEVELS_LEVEL01_H_ */

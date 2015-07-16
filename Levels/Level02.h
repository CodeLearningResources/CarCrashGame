/*
 * Level02.h
 *
 *  Created on: 17-apr.-2015
 *      Author: Thomas
 */

#ifndef LEVELS_LEVEL02_H_
#define LEVELS_LEVEL02_H_

#include "../Game/Level.h"

namespace CCG
{
	/*
	 * Level class
	 */
	class Level02 : public Level
	{
		public:
			Level02(void);
			Level02(const Level& level);
			~Level02(void);
	};
}

#endif /* LEVELS_LEVEL02_H_ */

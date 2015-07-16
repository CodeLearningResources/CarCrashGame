/*
 * Music.h
 *
 *  Created on: 14-apr.-2015
 *      Author: Thomas
 */

#ifndef GAME_MUSIC_H_
#define GAME_MUSIC_H_

namespace CCG
{
	/*
	 * Abstract class for music tracks
	 */
	class Music
	{
		public:
			virtual ~Music(void);

		protected:
			Music(void);
	};
}

#endif /* GAME_MUSIC_H_ */

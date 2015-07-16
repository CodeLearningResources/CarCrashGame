/*
 * SDLMusic.h
 *
 *  Created on: 4-apr.-2015
 *      Author: Thomas
 */

#ifndef SDLFACTORY_SDLMUSIC_H_
#define SDLFACTORY_SDLMUSIC_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

#include "../Game/Music.h"
#include "SDLTimer.h"

namespace CCG_SDL
{
	/*
	 * SDL implementation of the music class
	 */
	class SDLMusic : public CCG::Music
	{
		public:
			SDLMusic(Mix_Music* music);
			~SDLMusic(void);

			void setMusic(Mix_Music* music);
			void free(void);		//Deallocate music

			//////////////////////////////////////////
			// Following methods in development
			//////////////////////////////////////////
			void setPlayState(bool flag);
			void setPlayPosition(double position);

			bool getPlayState(void);
			Uint32 getPlayPosition(void);
			Uint32 getMusicLength(void);
			//////////////////////////////////////////
			// End in development
			//////////////////////////////////////////

			Mix_Music* getMusic(void);

			void play(bool gradually);
			void pause(void);
			void resume(void);
			void stop(bool gradually);

		private:
			Mix_Music* music;
			bool playing;
			SDLTimer playTime;

		protected:
			SDLMusic(void);
	};
}

#endif /* SDLFACTORY_SDLMUSIC_H_ */

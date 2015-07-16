/*
 * SDLSound.h
 *
 *  Created on: 4-apr.-2015
 *      Author: Thomas
 */

#ifndef SDLFACTORY_SDLSOUND_H_
#define SDLFACTORY_SDLSOUND_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

namespace CCG_SDL
{
	/*
	 * SDL implementation of the sound class
	 */
	class SDLSound
	{
		public:
			SDLSound(Mix_Chunk* sound);
			virtual ~SDLSound(void);

			void setSound(Mix_Chunk* sound);
			void free(void);		//Deallocate sound

			Mix_Chunk* getSound(void);

			void playSound(void);

		private:
			Mix_Chunk* sound;

		protected:
			SDLSound(void);
	};
}

#endif /* SDLFACTORY_SDLSOUND_H_ */

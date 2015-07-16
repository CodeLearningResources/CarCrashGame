/*
 * SDLRocket.h
 *
 *  Created on: 8-jun.-2015
 *      Author: Thomas
 */

#ifndef SDLFACTORY_SDLROCKET_H_
#define SDLFACTORY_SDLROCKET_H_

#include <SDL2/SDL.h>
#include "SDL2/SDL_image.h"

#include "../GameElements/Rocket.h"
#include "SDLTexture.h"
#include "SDLSound.h"

namespace CCG_SDL
{
	/*
	 * SDL implementation of the rocket class
	 */
	class SDLRocket : public CCG::Rocket
	{
		public:
			SDLRocket(SDL_Renderer* renderer, SDLTexture* texture, SDLSound* launchSound);
			~SDLRocket(void);

			void setTexture(SDLTexture* texture);
			SDLTexture* getTexture(void);
			void visible(bool flag);
			bool isVisible(void);
			void update(void);

			void playLaunchSound(void);

		private:
			bool visibility;
			SDLTexture* texture;
			SDLSound* launchSound;
			SDL_Renderer* renderer;

		protected:
			SDLRocket(void);
	};
}

#endif /* SDLFACTORY_SDLROCKET_H_ */

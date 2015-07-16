/*
 * SDLCar.h
 *
 *  Created on: 9-mrt.-2015
 *      Author: Thomas
 */

#ifndef SDLENGINE_SDLCAR_H_
#define SDLENGINE_SDLCAR_H_

#include <SDL2/SDL.h>
#include "SDL2/SDL_image.h"

#include "../GameElements/Car.h"
#include "SDLTexture.h"
#include "SDLSound.h"

namespace CCG_SDL
{
	/*
	 * SDL implementation of the car class
	 */
	class SDLCar : public CCG::Car
	{
		public:
			SDLCar(SDL_Renderer* renderer, SDLTexture* texture, SDLSound* crashSound);
			SDLCar(const SDLCar& car);
			~SDLCar(void);

			void setTexture(SDLTexture* texture);
			SDLTexture* getTexture(void);
			void visible(bool flag);
			bool isVisible(void);
			void update(void);

			void playCrashSound(void);
			void playNitroSound(void);
			void stopNitroSound(void);

		private:
			bool visibility;
			SDLTexture* texture;
			SDLSound* crashSound;
			SDL_Renderer* renderer;

		protected:
			SDLCar(void);
	};
}

#endif /* SDLENGINE_SDLCAR_H_ */

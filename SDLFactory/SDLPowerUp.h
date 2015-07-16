/*
 * SDLPowerUp.h
 *
 *  Created on: 19-apr.-2015
 *      Author: Thomas
 */

#ifndef SDLFACTORY_SDLPOWERUP_H_
#define SDLFACTORY_SDLPOWERUP_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "../GameElements/PowerUp.h"
#include "SDLTexture.h"

namespace CCG_SDL
{
	/*
	 * SDL implementation of the power-up class
	 */
	class SDLPowerUp : public CCG::PowerUp
	{
		public:
			SDLPowerUp(SDL_Renderer* renderer, SDLTexture* texture, CCG::PowerUpBonus bonus);
			SDLPowerUp(const SDLPowerUp& powerUp);
			~SDLPowerUp(void);

			void setTexture(SDLTexture* texture);
			SDLTexture* getTexture(void);
			void visible(bool flag);
			bool isVisible(void);
			void update(void);

		private:
			bool visibility;
			SDLTexture* texture;
			SDL_Renderer* renderer;

		protected:
			SDLPowerUp(void);
	};
}

#endif /* SDLFACTORY_SDLPOWERUP_H_ */

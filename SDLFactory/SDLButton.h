/*
 * SDLButton.h
 *
 *  Created on: 15-apr.-2015
 *      Author: Thomas
 */

#ifndef SDLFACTORY_SDLBUTTON_H_
#define SDLFACTORY_SDLBUTTON_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "../GameElements/Button.h"
#include "SDLTexture.h"
#include "SDLSound.h"

namespace CCG_SDL
{
	/*
	 * SDL implementation of the button class
	 */
	class SDLButton : public CCG::Button
	{
		public:
			SDLButton(SDL_Renderer* renderer, SDLTexture** texturePack, SDLSound* clickSound);
			~SDLButton(void);

			void setTexturePack(SDLTexture** texturePack);
			SDLTexture** getTexturePack(void);
			void visible(bool flag);
			bool isVisible(void);
			void update(void);

			void playClickSound(void);

		private:
			bool visibility;
			SDLTexture** texturePack;
			SDL_Renderer* renderer;
			SDLSound* clickSound;

		protected:
			SDLButton(void);
	};
}

#endif /* SDLFACTORY_SDLBUTTON_H_ */

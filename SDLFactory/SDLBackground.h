/*
 * SDLBackground.h
 *
 *  Created on: 16-mrt.-2015
 *      Author: Thomas
 */

#ifndef SDLENGINE_SDLBACKGROUND_H_
#define SDLENGINE_SDLBACKGROUND_H_

#include <SDL2/SDL.h>

#include "../GameElements/Background.h"
#include "SDLTexture.h"

namespace CCG_SDL
{
	/*
	 * SDL implementation of the background class
	 */
	class SDLBackground : public CCG::Background
	{
		public:
			SDLBackground(SDL_Renderer* renderer, SDLTexture* texture, CCG::ScrollDirection direction);
			SDLBackground(const SDLBackground& background);
			~SDLBackground(void);
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
			SDLBackground(void);
	};
}

#endif /* SDLENGINE_SDLBACKGROUND_H_ */

/*
 * SDLPicture.h
 *
 *  Created on: 16-apr.-2015
 *      Author: Thomas
 */

#ifndef SDLFACTORY_SDLPICTURE_H_
#define SDLFACTORY_SDLPICTURE_H_

#include <SDL2/SDL.h>
#include "SDL2/SDL_image.h"

#include "../GameElements/Picture.h"
#include "SDLTexture.h"

namespace CCG_SDL
{
	/*
	 * SDL implementation of the picture class
	 */
	class SDLPicture : public CCG::Picture
	{
		public:
			SDLPicture(SDL_Renderer* renderer, SDLTexture* texture);
			SDLPicture(const SDLPicture& picture);
			~SDLPicture(void);

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
			SDLPicture(void);
	};
}

#endif /* SDLFACTORY_SDLPICTURE_H_ */

/*
 * SDLFont.h
 *
 *  Created on: 4-apr.-2015
 *      Author: Thomas
 */

#ifndef SDLFACTORY_SDLFONT_H_
#define SDLFACTORY_SDLFONT_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

namespace CCG_SDL
{
	/*
	 * Font class needed for SDLText objects
	 */
	class SDLFont
	{
		public:
			SDLFont(TTF_Font* font);
			virtual ~SDLFont(void);

			void setFont(TTF_Font* font);
			void free(void);		//Deallocate font

			TTF_Font* getFont(void);

		private:
			TTF_Font* font;

		protected:
			SDLFont(void);
	};
}

#endif /* SDLFACTORY_SDLFONT_H_ */

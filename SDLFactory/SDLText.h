/*
 * SDLText.h
 *
 *  Created on: 23-mrt.-2015
 *      Author: Thomas
 */

#ifndef SDLENGINE_SDLTEXT_H_
#define SDLENGINE_SDLTEXT_H_

#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "../GameElements/Text.h"
#include "SDLTexture.h"
#include "SDLFont.h"

namespace CCG_SDL
{
	/*
	 * SDL implementation of the text class
	 */
	class SDLText : public CCG::Text
	{
		public:
			SDLText(SDL_Renderer* renderer, SDLFont* font, std::string text);
			SDLText(const SDLText& text);
			~SDLText(void);
			void setText(std::string text);
			void setWrapLength(uint32_t wrapLength);
			void setColor(uint8_t red, uint8_t green, uint8_t blue, uint8_t opaque);
			void setFont(SDLFont* font);
			SDLFont* getFont(void);
			void visible(bool flag);
			bool isVisible(void);
			void update(void);

		private:
			bool visibility;
			SDLTexture* texture;
			SDLFont* font;
			SDL_Renderer* renderer;

			int renderText(void);

		protected:
			SDLText(void);
	};
}

#endif /* SDLENGINE_SDLTEXT_H_ */

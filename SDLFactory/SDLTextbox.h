/*
 * SDLTextbox.h
 *
 *  Created on: 17-apr.-2015
 *      Author: Thomas
 */

#ifndef SDLFACTORY_SDLTEXTBOX_H_
#define SDLFACTORY_SDLTEXTBOX_H_

#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "../GameElements/Textbox.h"
#include "SDLText.h"
#include "SDLTexture.h"

namespace CCG_SDL
{
	/*
	 * SDL implementation of the textbox class
	 */
	class SDLTextbox : public CCG::Textbox
	{
		public:
			SDLTextbox(SDL_Renderer* renderer, SDLText* textFont, SDLTexture** texturePack);
			~SDLTextbox(void);

			void setText(std::string* text);
			void setTextFont(SDLText* textFont);
			void setTexturePack(SDLTexture** texturePack);

			void addCharacter(char character);
			void delCharacter(void);

			SDLText* getTextFont(void);
			SDLTexture** getTexturePack(void);
			void visible(bool flag);
			bool isVisible(void);
			void update(void);
			void updateText(void);

		private:
			bool visibility;
			SDLTexture** texturePack;
			SDLText* textFont;
			SDL_Renderer* renderer;

		protected:
			SDLTextbox(void);
	};
}

#endif /* SDLFACTORY_SDLTEXTBOX_H_ */

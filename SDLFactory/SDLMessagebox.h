/*
 * SDLMessagebox.h
 *
 *  Created on: 16-jun.-2015
 *      Author: Thomas
 */

#ifndef SDLFACTORY_SDLMESSAGEBOX_H_
#define SDLFACTORY_SDLMESSAGEBOX_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

#include "../GameElements/Messagebox.h"
#include "SDLButton.h"
#include "SDLTexture.h"
#include "SDLSound.h"
#include "SDLText.h"

namespace CCG_SDL
{
	/*
	 * SDL implementation of the messagebox class
	 */
	class SDLMessagebox : public CCG::Messagebox
	{
		public:
			SDLMessagebox(SDL_Renderer* renderer, SDLTexture* texture, SDLButton* button, SDLText* messageFont, SDLText* buttonFont, std::string* messageText, std::string* buttonText1, std::string* buttonText2);
			~SDLMessagebox(void);

			void setBackgroundTexture(SDLTexture* texture);
			SDLTexture* getBackgroundTexture(void);
			void visible(bool flag);
			bool isVisible(void);
			void update(void);

			void setMessageText(std::string* text);
			void setButtons(std::string* buttonText1, std::string* buttonText2);

			void updateProportions(void);
			int checkMessageboxState(int posX, int posY, bool pressed);

		private:
			bool visibility;
			SDLTexture* texture;
			SDL_Renderer* renderer;
			SDLButton* button1;
			SDLButton* button2;
			SDLText* messageFont;
			SDLText* button1Font;
			SDLText* button2Font;

		protected:
			SDLMessagebox(void);
	};
}

#endif /* SDLFACTORY_SDLMESSAGEBOX_H_ */

/*
 * SDLCheckbox.h
 *
 *  Created on: 10-mei-2015
 *      Author: Thomas
 */

#ifndef SDLFACTORY_SDLCHECKBOX_H_
#define SDLFACTORY_SDLCHECKBOX_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "../GameElements/Checkbox.h"
#include "SDLTexture.h"

namespace CCG_SDL
{
	enum CheckboxElements
	{
		CHECKBOX_ELEMENT_NORMAL,
		CHECKBOX_ELEMENT_HIGHLIGHTED,
		CHECKBOX_ELEMENT_CHECKTICK,
		CHECKBOX_ELEMENT_MAX
	};

	/*
	 * SDL implementation of the checkbox class
	 */

	class SDLCheckbox : public CCG::Checkbox
	{
		public:
			SDLCheckbox(SDL_Renderer* renderer, SDLTexture** texturePack);
			~SDLCheckbox(void);

			void setTexturePack(SDLTexture** texturePack);
			SDLTexture** getTexturePack(void);
			void visible(bool flag);
			bool isVisible(void);
			void update(void);

		private:
			bool visibility;
			SDLTexture** texturePack;
			SDLTexture* textureCheckTick;
			SDL_Renderer* renderer;

		protected:
			SDLCheckbox(void);
	};
}

#endif /* SDLFACTORY_SDLCHECKBOX_H_ */

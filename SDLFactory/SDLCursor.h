/*
 * SDLCursor.h
 *
 *  Created on: 19-jun.-2015
 *      Author: Thomas
 */

#ifndef SDLFACTORY_SDLCURSOR_H_
#define SDLFACTORY_SDLCURSOR_H_

#include <SDL2/SDL.h>
#include "SDL2/SDL_image.h"

#include "../GameElements/Cursor.h"
#include "SDLTexture.h"

namespace CCG_SDL
{
	/*
	 * SDL implementation of the cursor class
	 */
	class SDLCursor : public CCG::Cursor
	{
		public:
			SDLCursor(SDL_Renderer* renderer, SDLTexture** texturePack);
			~SDLCursor(void);

			void setTexture(SDLTexture** texture);
			void visible(bool flag);
			bool isVisible(void);
			void update(void);

			void setMousePosition(float posX, float posY, bool clicking);

		private:
			bool visibility;
			SDLTexture** textures;
			SDL_Renderer* renderer;

		protected:
			SDLCursor(void);
	};
}

#endif /* SDLFACTORY_SDLCURSOR_H_ */

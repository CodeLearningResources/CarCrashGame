/*
 * SDLTexture.h
 *
 *  Created on: 15-mrt.-2015
 *      Author: Thomas
 */

#ifndef SDLENGINE_SDLTEXTURE_H_
#define SDLENGINE_SDLTEXTURE_H_

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

namespace CCG_SDL
{
	/*
	 * SDL class for textures used in game objects
	 */
	class SDLTexture
	{
		public:
			SDLTexture(SDL_Texture* texture, int width, int height);
			virtual ~SDLTexture(void);

			void setTexture(SDL_Texture* texture, int width, int height);
			void free(void);			//Deallocate texture
			void setAlphaBlending(bool flag);
			void setAlpha(int alpha);

			SDL_Texture* getTexture(void) const;
			int getWidth(void) const;
			int getHeight(void) const;

		private:
			SDL_Texture* texture;		//The actual hardware texture

			int textureWidth;			//Image width
			int textureHeight;			//Image height

		protected:
			SDLTexture(void);
	};
}

#endif /* SDLENGINE_SDLTEXTURE_H_ */

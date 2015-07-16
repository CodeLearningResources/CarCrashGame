/*
 * SDLHUD.h
 *
 *  Created on: 30-mrt.-2015
 *      Author: Thomas
 */

#ifndef SDLFACTORY_SDLHUD_H_
#define SDLFACTORY_SDLHUD_H_

#include <string>
#include <SDL2/SDL.h>

#include "../GameElements/HUD.h"
#include "../Game/Player.h"
#include "SDLTexture.h"
#include "SDLText.h"

namespace CCG_SDL
{
	enum HUDElements
	{
		HUD_ELEMENT_STATUSBAR,
		HUD_ELEMENT_HEALTHBAR,
		HUD_ELEMENT_NITROBAR,
		HUD_ELEMENT_INVINCIBILITY_STATUS,
		HUD_ELEMENT_PLAYER01_STATUS,
		HUD_ELEMENT_PLAYER02_STATUS,
		HUD_ELEMENT_PLAYER03_STATUS,
		HUD_ELEMENT_PLAYER04_STATUS,
		HUD_ELEMENT_ROCKETS,
		HUD_ELEMENT_MAX
	};

	/*
	 * SDL implementation of the HUD class
	 */
	class SDLHUD : public CCG::HUD
	{
		public:
			SDLHUD(SDL_Renderer* renderer, SDLTexture** texturePack, SDLText* nameText, SDLText* scoreText, SDLText* rocketsText);
			~SDLHUD(void);

			void visible(bool flag);
			bool isVisible(void);
			void update(void);

		private:
			bool visibility;
			SDLTexture* statusbarTexture;
			SDLTexture* healthbarTexture;
			SDLTexture* nitrobarTexture;
			SDLTexture* invincibilityTexture;
			SDLTexture** playerStatusTexture;
			SDLTexture* rocketTexture;
			SDLText* nameText;
			SDLText* scoreText;
			SDLText* rocketsText;
			SDL_Renderer* renderer;

		protected:
			SDLHUD(void);
	};
}

#endif /* SDLFACTORY_SDLHUD_H_ */

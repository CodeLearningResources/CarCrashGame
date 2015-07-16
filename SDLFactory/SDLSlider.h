/*
 * SDLSlider.h
 *
 *  Created on: 27-apr.-2015
 *      Author: Thomas
 */

#ifndef SDLFACTORY_SDLSLIDER_H_
#define SDLFACTORY_SDLSLIDER_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "../GameElements/Slider.h"
#include "SDLTexture.h"

namespace CCG_SDL
{
	enum SliderElements
	{
		SLIDER_ELEMENT_BAR,
		SLIDER_ELEMENT_MARKER,
		SLIDER_ELEMENT_MAX
	};

	/*
	 * SDL implementation of the slider class
	 */
	class SDLSlider : public CCG::Slider
	{
		public:
			SDLSlider(SDL_Renderer* renderer, SDLTexture** texturePack);
			~SDLSlider(void);

			void visible(bool flag);
			bool isVisible(void);
			void update(void);

		private:
			bool visibility;
			SDLTexture* sliderBarTexture;
			SDLTexture* sliderMarkerTexture;
			SDL_Renderer* renderer;

		protected:
			SDLSlider(void);
	};
}

#endif /* SDLFACTORY_SDLSLIDER_H_ */

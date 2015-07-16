/*
 * SDLAnimation.h
 *
 *  Created on: 4-mei-2015
 *      Author: Thomas
 */

#ifndef SDLFACTORY_SDLANIMATION_H_
#define SDLFACTORY_SDLANIMATION_H_

#include <math.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "../GameElements/Animation.h"
#include "SDLTexture.h"

namespace CCG_SDL
{
	/*
	 * SDL implementation of the animation class
	 */
	class SDLAnimation : public CCG::Animation
	{
		public:
			SDLAnimation(SDL_Renderer* renderer, SDLTexture* animationTexture, int spriteWidth, int spriteHeight, int animationRows, int animationColumns, float animationNextFrameTime);
			virtual ~SDLAnimation(void);

			void setAnimationFrameTime(float time);			//Set the time between two frames
			void setSpriteSize(int width, int height);		//Set the size of one frame
			void setAnimationSlots(int rows, int columns);	//Set the columns and rows on the animation sheet
			void setAnimationCurrentFrame(int frame);		//Set current displayed frame
			void setAnimationRepeat(bool flag);				//Repeat animation

			float getAnimationFrameTime(void) const;
			void getSpriteSize(int* width, int* height);
			void getAnimationSlots(int* rows, int* columns);
			int getAnimationCurrentFrame(void) const;
			bool getAnimationRepeatStatus(void) const;
			bool isRunning(void) const;

			void run(void);
			void stop(void);

			void visible(bool flag);
			bool isVisible(void);
			void update(void);
			void updateAnimation(float timeStep);

		private:
			bool visibility;
			SDL_Renderer* renderer;
			SDLTexture* animationTexture;

			int spriteWidth;
			int spriteHeight;
			int animationRows;
			int animationColumns;
			int currentAnimationRow;
			int currentAnimationColumn;
			float animationFrameTime;			//Time between two frames
			float previousFrameTime;			//Time stamp of the last frame
			bool repeat;
			bool animationRunning;

		protected:
			SDLAnimation(void);
	};
}

#endif /* SDLFACTORY_SDLANIMATION_H_ */

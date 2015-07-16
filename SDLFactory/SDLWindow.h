/*
 * SDLWindow.h
 *
 *  Created on: 23-mrt.-2015
 *      Author: Thomas
 */

#ifndef SDLENGINE_SDLWINDOW_H_
#define SDLENGINE_SDLWINDOW_H_

#include <stdio.h>
#include <SDL2/SDL.h>

#include "../Game/Window.h"
#include "SDLTexture.h"
#include "SDLTimer.h"

namespace CCG_SDL
{
	/*
	 * SDL implementation of the window class
	 */
	class SDLWindow : public CCG::Window
	{
		public:
			SDLWindow(SDL_Window* window, SDL_Renderer* renderer);
			~SDLWindow(void);

			int showWindow(void);
			int hideWindow(void);
			int updateWindow(void);

			void setIcon(SDL_Surface* icon);
			void setTitle(const char* title);
			void setSize(int width, int height);
			void setFPSCap(int cap);
			int setHardwareAcceleration(bool flag);
			int setVSync(bool flag);

			int getFPSCap(void) const;
			bool getHardwareAcceleration(void) const;
			bool getVSync(void) const;

			SDL_Renderer* getRenderer(void) const;

			//////////////////////////////////////////
			// Following methods in development
			//////////////////////////////////////////
			int updateRenderSettings(void);
			SDLTexture* getScreenShotTexture(void);
			//////////////////////////////////////////
			// End in development
			//////////////////////////////////////////

		private:
			int FPSCap;
			bool hardwareAccelerated;
			bool VSync;

			SDLTimer* capTimer;	//Timer for the frames per seconds cap
			SDL_Window* window;
			SDL_Renderer* renderer;
			SDLTexture* screenShotTexture;

		protected:
			SDLWindow(void);
	};
}

#endif /* SDLENGINE_SDLWINDOW_H_ */

/*
 * SDLWindow.cpp
 *
 *  Created on: 23-mrt.-2015
 *      Author: Thomas
 */

#include "SDLWindow.h"

using namespace CCG_SDL;

SDLWindow::SDLWindow() : CCG::Window()
{
	FPSCap = 0;					//FPS cap turned off

	window = NULL;
	renderer = NULL;
	capTimer = new SDLTimer();
	screenShotTexture = NULL;
	hardwareAccelerated = true;
	VSync = true;
}

SDLWindow::SDLWindow(SDL_Window* window, SDL_Renderer* renderer) : CCG::Window()
{
	this->FPSCap = 0;			//FPS cap turned off

	this->window = window;
	this->renderer = renderer;
	this->capTimer = new SDLTimer();
	this->screenShotTexture = NULL;
	this->hardwareAccelerated = true;
	this->VSync = true;
}

SDLWindow::~SDLWindow()
{
	//Destroy renderer
	if(renderer != NULL)
	{
		SDL_DestroyRenderer(renderer);
	}

	//Destroy window
	if(window != NULL)
	{
		SDL_DestroyWindow(window);
	}

	if(screenShotTexture != NULL)
	{
		delete(screenShotTexture);
	}

	//Destroy timer
	delete(capTimer);
}

int SDLWindow::showWindow()
{
	if(window != NULL)
	{
		SDL_ShowWindow(window);
	}
	else
	{
		printf("Window could not be showed! No window is available.\n");
		return -1;
	}

	return 0;
}

int SDLWindow::hideWindow()
{
	if(window != NULL)
	{
		SDL_HideWindow(window);
	}
	else
	{
		printf("Window could not be hidden! No window is available.\n");
		return -1;
	}

	return 0;
}

int SDLWindow::updateWindow()
{
	int frameTicks = capTimer->getTicks();

	//Update the renderer
	if(renderer != NULL)
	{
		//Limit the rendered frames per seconds
		if(FPSCap != 0)
		{
			if(frameTicks < (1000 / FPSCap) && frameTicks != 0)
			{
				//Wait remaining time
				SDL_Delay((1000 / FPSCap) - frameTicks);
			}
			capTimer->start();
		}
		else
		{
			capTimer->stop();
		}

		//Display all rendered textures on window
		SDL_RenderPresent(renderer);

		//Clear render buffer
		SDL_RenderClear(renderer);
	}
	else
	{
		printf("Window could not be updated! No renderer is available.\n");
		return -1;
	}

	return 0;
}

void SDLWindow::setIcon(SDL_Surface* icon)
{
	if(window != NULL)
	{
		SDL_SetWindowIcon(this->window, icon);
	}
}

void SDLWindow::setTitle(const char* title)
{
	if(window != NULL)
	{
		SDL_SetWindowTitle(window, title);
	}
}

void SDLWindow::setSize(int width, int height)
{

}

void SDLWindow::setFPSCap(int cap)
{
	this->FPSCap = cap;
}

int SDLWindow::setHardwareAcceleration(bool flag)
{
	this->hardwareAccelerated = flag;

	return updateRenderSettings();
}

int SDLWindow::setVSync(bool flag)
{
	this->VSync = flag;

	return updateRenderSettings();
}

int SDLWindow::getFPSCap() const
{
	return this->FPSCap;
}

bool SDLWindow::getHardwareAcceleration() const
{
	return this->hardwareAccelerated;
}

bool SDLWindow::getVSync() const
{
	return this->VSync;
}

SDL_Renderer* SDLWindow::getRenderer() const
{
	return this->renderer;
}

int SDLWindow::updateRenderSettings()
{
/*	int renderFlags = 0;
	SDL_Renderer* newRenderer;
	SDL_Window* newWindow;

	if(this->hardwareAccelerated)
	{
		renderFlags = renderFlags | SDL_RENDERER_ACCELERATED;
	}
	else
	{
		renderFlags |= SDL_RENDERER_ACCELERATED;
	}

printf("RENDERFLAGS: %d %d\n", renderFlags, hardwareAccelerated);

	if(this->VSync)
	{
		renderFlags |= SDL_RENDERER_PRESENTVSYNC;
	}

	printf("%d %d %d\n", renderFlags, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC, SDL_RENDERER_ACCELERATED);

//newWindow = SDL_CreateWindow(NULL, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 500, 500, 0);
SDL_DestroyRenderer(this->renderer);

	//Create new renderer
	newRenderer = SDL_CreateRenderer(this->window, -1, renderFlags);

	if(newRenderer == NULL)
	{
		printf("Renderer could not be initialized with new settings!\n");

		return -1;
	}

	//SDL_Delay(5000);

//SDL_DestroyWindow(newWindow);
	//Destroy previous renderer
	//SDL_DestroyRenderer(this->renderer);

	//Create renderer
	this->renderer = newRenderer;
*/
	return 0;
}

SDLTexture* SDLWindow::getScreenShotTexture()
{
/*
	SDL_Surface* windowSurface;
	SDL_Texture* newTexture;

	windowSurface = SDL_GetWindowSurface(this->window);

	if(this->screenShotTexture != NULL)
	{
		delete(this->screenShotTexture);
		this->screenShotTexture = NULL;
	}

	newTexture = SDL_CreateTextureFromSurface(renderer, windowSurface);

	this->screenShotTexture = new SDLTexture(newTexture, windowSurface->w, windowSurface->h);

	return this->screenShotTexture;
*/
	return NULL;
}

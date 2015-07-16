/*
 * SDLSlider.cpp
 *
 *  Created on: 27-apr.-2015
 *      Author: Thomas
 */

#include "SDLSlider.h"

using namespace CCG_SDL;

SDLSlider::SDLSlider() : CCG::Slider()
{
	this->visibility = false;
	this->sliderBarTexture = NULL;
	this->sliderMarkerTexture = NULL;
	this->renderer = NULL;
}

SDLSlider::SDLSlider(SDL_Renderer* renderer, SDLTexture** texturePack) : CCG::Slider()
{
	this->visibility = false;
	this->sliderBarTexture = texturePack[SLIDER_ELEMENT_BAR];
	this->sliderMarkerTexture = texturePack[SLIDER_ELEMENT_MARKER];
	this->renderer = renderer;
}

SDLSlider::~SDLSlider()
{

}

void SDLSlider::visible(bool flag)
{
	this->visibility = flag;
}

bool SDLSlider::isVisible()
{
	return this->visibility;
}

void SDLSlider::update()
{
	if(sliderBarTexture == NULL || sliderMarkerTexture == NULL)
	{
		return;
	}

	if(visibility)
	{
		float markerSizeX = getSizeY() / 2;		//Ratio W:H = 1:2
		float markerPosX = getPosX() + ((getSizeX() - markerSizeX) * (getValue() / 100.0f));

		//Slider bar texture
		SDL_Rect renderBoxBar = {(int)getPosX(), (int)getPosY(), (int)getSizeX(), (int)getSizeY()};
		SDL_RenderCopyEx(renderer, sliderBarTexture->getTexture(), NULL, &renderBoxBar, getRotation() + getRelRotation(), NULL, SDL_FLIP_NONE);

		//Slider marker texture
		SDL_Rect renderBoxMarker = {(int)markerPosX, (int)getPosY(), (int)markerSizeX, (int)getSizeY()};
		SDL_RenderCopyEx(renderer, sliderMarkerTexture->getTexture(), NULL, &renderBoxMarker, getRotation() + getRelRotation(), NULL, SDL_FLIP_NONE);
	}
}

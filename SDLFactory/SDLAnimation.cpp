/*
 * SDLAnimation.cpp
 *
 *  Created on: 4-mei-2015
 *      Author: Thomas
 */

#include "SDLAnimation.h"

using namespace CCG_SDL;

SDLAnimation::SDLAnimation() : CCG::Animation()
{
	visibility = false;
	renderer = NULL;
	animationTexture = NULL;

	spriteWidth = 0;
	spriteHeight = 0;
	animationRows = 0;
	animationColumns = 0;
	currentAnimationRow = 0;
	currentAnimationColumn = 0;
	animationFrameTime = 0.0f;
	previousFrameTime = 0.0f;
	repeat = false;
	animationRunning = false;
}

SDLAnimation::SDLAnimation(SDL_Renderer* renderer, SDLTexture* animationTexture, int spriteWidth, int spriteHeight, int animationRows, int animationColumns, float animationNextFrameTime) : CCG::Animation()
{
	this->visibility = false;
	this->renderer = renderer;
	this->animationTexture = animationTexture;

	this->spriteWidth = spriteWidth;
	this->spriteHeight = spriteHeight;
	this->animationRows = animationRows;
	this->animationColumns = animationColumns;
	this->currentAnimationRow = 0;
	this->currentAnimationColumn = 0;
	this->animationFrameTime = animationNextFrameTime;
	this->previousFrameTime = 0.0f;
	this->repeat = false;
	this->animationRunning = false;
}

SDLAnimation::~SDLAnimation()
{

}

void SDLAnimation::setAnimationFrameTime(float time)
{
	this->animationFrameTime = time;
}

void SDLAnimation::setSpriteSize(int width, int height)
{
	this->spriteWidth = width;
	this->spriteHeight = height;
}

void SDLAnimation::setAnimationSlots(int rows, int columns)
{
	this->animationRows = rows;
	this->animationColumns = columns;
}

void SDLAnimation::setAnimationCurrentFrame(int frame)
{
	if(frame > (animationRows * animationColumns) || frame < 0)
	{
		//Frame does not exist on texture, set to frame 0
		this->currentAnimationRow = 0;
		this->currentAnimationColumn = 0;
	}
	else
	{
		//Determine the column and row of the frame on the texture
		this->currentAnimationRow = floor(frame / this->animationColumns);
		this->currentAnimationColumn = frame % this->animationColumns;
	}
}

void SDLAnimation::setAnimationRepeat(bool flag)
{
	this->repeat = flag;
}

float SDLAnimation::getAnimationFrameTime() const
{
	return this->animationFrameTime;
}

void SDLAnimation::getSpriteSize(int* width, int* height)
{
	*width = this->spriteWidth;
	*height = this->spriteHeight;
}

void SDLAnimation::getAnimationSlots(int* rows, int* columns)
{
	*rows = this->animationRows;
	*columns = this->animationColumns;
}

int SDLAnimation::getAnimationCurrentFrame() const
{
	//Animation frames order per row, from left to right
	int currentFrame = ((this->currentAnimationRow * this->animationColumns) + this->currentAnimationColumn);

	return currentFrame;
}

bool SDLAnimation::getAnimationRepeatStatus() const
{
	return this->repeat;
}

bool SDLAnimation::isRunning() const
{
	return this->animationRunning;
}

void SDLAnimation::run()
{
	previousFrameTime = 0.0f;
	this->animationRunning = true;
}

void SDLAnimation::stop()
{
	this->animationRunning = false;
}

void SDLAnimation::visible(bool flag)
{
	this->visibility = flag;
}

bool SDLAnimation::isVisible()
{
	return this->visibility;
}

void SDLAnimation::update()
{
	SDL_Rect renderBox = {(int)getPosX(), (int)getPosY(), (int)getSizeX(), (int)getSizeY()};
	SDL_Rect frameBox = {(int)currentAnimationColumn * spriteWidth, (int)currentAnimationRow * spriteHeight, (int)spriteWidth, (int)spriteHeight};
	SDL_RenderCopyEx(renderer, animationTexture->getTexture(), &frameBox, &renderBox, getRotation() + getRelRotation(), NULL, SDL_FLIP_NONE);
}

void SDLAnimation::updateAnimation(float timeStep)
{
	int numberOfFrames = 1;
	int newFrame = 0;

	if(animationRunning)
	{
		previousFrameTime += timeStep;

		if(previousFrameTime >= animationFrameTime)
		{
			//Show next frame
			if(animationFrameTime > 0)
			{
				numberOfFrames = previousFrameTime / animationFrameTime;
			}

			newFrame = getAnimationCurrentFrame() + numberOfFrames;

			if(newFrame >= animationRows * animationColumns)
			{
				if(!this->repeat)
				{
					//Animation has ended
					animationFrameTime = 0.0f;

					this->setAnimationCurrentFrame((animationRows * animationColumns) - 1);
					this->animationRunning = false;

					return;
				}
				else
				{
					newFrame = newFrame % (animationRows * animationColumns);
				}
			}

			this->setAnimationCurrentFrame(newFrame);

			//Reset frame time
			previousFrameTime = 0.0f;
		}
	}
}

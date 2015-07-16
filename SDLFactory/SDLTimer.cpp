/*
 * SDLTimer.cpp
 *
 *  Created on: 23-mrt.-2015
 *      Author: Thomas
 */

#include "SDLTimer.h"

using namespace CCG_SDL;

SDLTimer::SDLTimer() : CCG::Timer()
{
	startTime = 0;
	pausedTime = 0;

	startStatus = false;
	pauseStatus = false;
}

SDLTimer::~SDLTimer()
{

}

void SDLTimer::start()
{
	//Start the timer
	startStatus = true;
	pauseStatus = false;

	//Get current time
	startTime = SDL_GetTicks();
	pausedTime = 0;
}

void SDLTimer::stop()
{
	//Stop the timer
	startStatus = false;
	pauseStatus = false;

	//Clear time
	startTime = 0;
	pausedTime = 0;
}

void SDLTimer::reset()
{
	//Get current time
	startTime = SDL_GetTicks();
	pausedTime = 0;
}

void SDLTimer::pause()
{
	if(startStatus && !pauseStatus)
	{
		//Pause the timer
		pauseStatus = true;

		//Set pause time
		pausedTime = SDL_GetTicks() - startTime;
		startTime = 0;
	}
}

void SDLTimer::unpause()
{
	if(startStatus && pauseStatus)
	{
		//Unpause the timer
		pauseStatus = false;

		//Set start time
		startTime = SDL_GetTicks() - pausedTime;
		pausedTime = 0;
	}
}

uint32_t SDLTimer::getTicks() const
{
	if(startStatus)
	{
		if(pauseStatus)
		{
			//Return the number of ticks when the timer was paused
			return pausedTime;
		}
		else
		{
			//Return the current time
			return (SDL_GetTicks() - startTime);
		}
	}

	//Timer is not running
	return 0;
}

bool SDLTimer::isStarted()
{
	return startStatus;
}

bool SDLTimer::isPaused()
{
	return pauseStatus;
}

/*
 * GameSplash.cpp
 *
 *  Created on: 12-apr.-2015
 *      Author: Thomas
 */

#include "GameSplash.h"

using namespace CCG;

GameSplash::GameSplash() : GameState()
{
	skip = false;
}

GameSplash::GameSplash(GameFactory* factory, GameStateManager* stateManager, GameManager* gameManager) : GameState(factory, stateManager, gameManager)
{
	skip = false;
}

GameSplash::~GameSplash()
{

}

void GameSplash::initialize()
{
	frameTimer = factory->getTimer();
	fadeoutTimer = factory->getTimer();
	factory->getCursor()->visible(false);

	//Initialize level background
	splashArt = factory->getPicture(PICTURE_SPLASHART);
	splashArt->setPos(112, 84);
	splashArt->setSize(800, 600);
	splashArt->visible(true);

	fadeoutTimer->start();
}

void GameSplash::release()
{
	delete(frameTimer);
	frameTimer = NULL;

	delete(fadeoutTimer);
	fadeoutTimer = NULL;
}

void GameSplash::pause()
{
	this->frameTimer->pause();
	this->fadeoutTimer->pause();
}

void GameSplash::resume()
{
	this->fadeoutTimer->pause();
	this->fadeoutTimer->unpause();
}

void GameSplash::handleEvents(Event* event)
{
	if(event != NULL)
	{
		switch(event->getType())
		{
			case GAME_QUIT:
				stateManager->exitGame();
				break;
			case KEYBOARD_EVENT:
				if(event->getKeyEvent()->getKeyValue() == KEY_ESCAPE && event->getButtonState() == BUTTON_PRESSED)
				{
					stateManager->exitGame();
				}
				else if(event->getKeyEvent()->getKeyValue() == KEY_SPACE && event->getButtonState() == BUTTON_PRESSED)
				{
					skip = true;
				}
				break;
			default:
				break;
		}
		delete(event);
		event = NULL;
	}
}

void GameSplash::update()
{
	//float timeStep = 0.0f;
	float fadeoutTime = 0.0f;

	//Calculate time step
	if(!frameTimer->isPaused())
	{
	//	timeStep = frameTimer->getTicks() / 1000.f;
	}

	fadeoutTime = fadeoutTimer->getTicks() / 1000.f;

	splashArt->update();

	if(!frameTimer->isPaused())
	{
		frameTimer->start();
	}

	//Start fade out after 2 seconds
	if(fadeoutTime >= 2.f || skip)
	{
		stateManager->setState(new GameStartMenu(factory, stateManager, gameManager));
	}
}

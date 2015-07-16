/*
 * GameFactory.cpp
 *
 *  Created on: 9-mrt.-2015
 *      Author: Thomas
 */

#include "GameFactory.h"

using namespace CCG;

GameFactory::GameFactory()
{
	SCREEN_WIDTH = 1024;
	SCREEN_HEIGHT = 768;
}

GameFactory::GameFactory(int width, int height)
{
	SCREEN_WIDTH = width;
	SCREEN_HEIGHT = height;
}

GameFactory::~GameFactory()
{
	//Destruct GameEngine object
}

int GameFactory::getScreenWidth()
{
	return SCREEN_WIDTH;
}

int GameFactory::getScreenHeight()
{
	return SCREEN_HEIGHT;
}

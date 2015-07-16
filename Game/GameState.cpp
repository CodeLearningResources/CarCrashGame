/*
 * GameState.cpp
 *
 *  Created on: 31-mrt.-2015
 *      Author: Thomas
 */

#include "GameState.h"

using namespace CCG;

GameState::GameState()
{
	stateManager = NULL;
	factory = NULL;
	gameManager = NULL;
}

GameState::GameState(GameFactory* factory, GameStateManager* stateManager, GameManager* gameManager)
{
	this->factory = factory;
	this->stateManager = stateManager;
	this->gameManager = gameManager;
}

GameState::~GameState()
{

}


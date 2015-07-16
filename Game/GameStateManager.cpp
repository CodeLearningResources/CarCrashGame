/*
 * GameStateManager.cpp
 *
 *  Created on: 31-mrt.-2015
 *      Author: Thomas
 */

#include "GameStateManager.h"
#include "GameState.h"		//Include in cpp-file for circular include

using namespace CCG;

GameStateManager::GameStateManager()
{
	states = new std::vector<GameState*>();
	running = true;
}

GameStateManager::~GameStateManager()
{
	this->releaseStack();
	delete(states);
}

void GameStateManager::releaseStack()
{
	//Clear the state stack
	while(!states->empty())
	{
		states->back()->release();
		delete(states->back());
		states->pop_back();
	}
}

void GameStateManager::setState(GameState* state)
{
	//Clear the state stack
	this->releaseStack();

	//Initialize new state and put on stack
	states->push_back(state);
	states->back()->initialize();
}

void GameStateManager::pushState(GameState* state)
{
	//Pause the current state
	if(!states->empty())
	{
		states->back()->pause();
	}

	//Initialize new state and put on stack
	states->push_back(state);
	states->back()->initialize();
}

void GameStateManager::popState()
{
	//Release the current state
	if(!states->empty())
	{
		states->back()->release();
		delete(states->back());
		states->pop_back();
	}

	//Resume previous state
	if(!states->empty())
	{
		states->back()->resume();
	}
}

void GameStateManager::exitGame()
{
	this->running = false;
}

GameState* GameStateManager::getState()
{
	GameState* currentState;

	//Get the current state from the state stack
	if(!states->empty())
	{
		currentState = states->back();
		return currentState;
	}

	return NULL;
}

bool GameStateManager::getRunningState()
{
	return this->running;
}

void GameStateManager::handleEvents(Event* event)
{
	if(!states->empty())
	{
		states->back()->handleEvents(event);
	}
}

void GameStateManager::update()
{
	if(!states->empty())
	{
		states->back()->update();
	}
}

/*
 * GameManager.cpp
 *
 *  Created on: 5-apr.-2015
 *      Author: Thomas
 */

#include "GameManager.h"

using namespace CCG;

GameManager::GameManager()
{
	this->currentPlayer = new Player();
	this->levelManager = new Levels();
	//this->highscores = new GameHighscore(this->levelManager->availableLevels());
}

GameManager::~GameManager()
{
	delete(currentPlayer);
	delete(levelManager);
	//delete(highscores);
}

void GameManager::setThisPlayer(Player* player)
{
	//Unload pre-existing player
	delete(currentPlayer);

	this->currentPlayer = player;
}

Player* GameManager::getThisPlayer()
{
	return this->currentPlayer;
}

Level* GameManager::getLevel(int level)
{
	return this->levelManager->getLevel(level);
}

int GameManager::availableLevels(void)
{
	return this->levelManager->availableLevels();
}

bool GameManager::addHighscore(int level, std::string playerName, int score)
{
	//return this->highscores->addHighscore(level, playerName, score);

	return false;
}

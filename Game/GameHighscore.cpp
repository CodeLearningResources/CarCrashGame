/*
 * GameHighscore.cpp
 *
 *  Created on: 20-jun.-2015
 *      Author: Thomas
 */

#include "GameHighscore.h"

using namespace CCG;

GameHighscore::GameHighscore()
{
	maxLevels = 0;
	highscoreList = NULL;
}

GameHighscore::GameHighscore(int maxLevels)
{
	this->maxLevels = maxLevels;
	this->highscoreList = new std::vector< std::list<HighscoreEntry*>* >;

	for(int i = 0; i < maxLevels; i++)
	{
		this->highscoreList->push_back(new std::list<HighscoreEntry*>);
	}
}

GameHighscore::~GameHighscore()
{
	std::vector< std::list<HighscoreEntry*>* >::iterator itVector = highscoreList->begin();

	while(itVector != highscoreList->end())
	{
		std::list<HighscoreEntry*>::iterator itList = (*itVector)->begin();

		while(itList != (*itVector)->end())
		{
			itList = (*itVector)->erase(itList);
		}

		itVector = highscoreList->erase(itVector);
	}

	delete(highscoreList);

	highscoreList = NULL;
}

void GameHighscore::resetHighscores()
{
	std::vector< std::list<HighscoreEntry*>* >::iterator itVector = highscoreList->begin();

	while(itVector != highscoreList->end())
	{
		std::list<HighscoreEntry*>::iterator itList = (*itVector)->begin();

		while(itList != (*itVector)->end())
		{
			itList = (*itVector)->erase(itList);
		}
	}
}

int GameHighscore::loadHighscores(const char* fileLocation)
{
	return 0;
}

int GameHighscore::saveHighscores(const char* fileLocation)
{
	return 0;
}

bool GameHighscore::addHighscore(int level, std::string playerName, int score)
{
	if(level < 0 || level >= maxLevels)
	{
		//Level not in range
		return false;
	}

	if(!highscoreList->at(level)->empty())
	{
		if(highscoreList->at(level)->back()->getScore() > score && highscoreList->at(level)->size() >= NUMBER_OF_TOPSCORES)
		{
			//No new highscore achieved
			return false;
		}
		else
		{
			//New highscore achieved
			std::list<HighscoreEntry*>::iterator it = highscoreList->at(level)->begin();
			bool positionFound = false;

			while(!positionFound && it != highscoreList->at(level)->end())
			{
				if((*it)->getScore() <= score)
				{
					//New place found
					positionFound = true;
				}
				else
				{
					it++;
				}
			}

			if(positionFound)
			{
				if(highscoreList->at(level)->size() >= NUMBER_OF_TOPSCORES)
				{
					//Delete last entry to maintain list size
					highscoreList->at(level)->pop_back();
				}

				//Insert new entry in list
				highscoreList->at(level)->insert(it, new HighscoreEntry(playerName, score));
			}
			else
			{
				//Add entry to the back of the list
				highscoreList->at(level)->push_back(new HighscoreEntry(playerName, score));
			}

			return true;
		}
	}
	else
	{
		//Ranklist is empty
		highscoreList->at(level)->push_front(new HighscoreEntry(playerName, score));

		return true;
	}
}

std::list<HighscoreEntry*>* GameHighscore::getHighscores(int level)
{
	if(level < 0 || level >= maxLevels)
	{
		//Level not in range
		return NULL;
	}

	return this->highscoreList->at(level);
}

int GameHighscore::getNumberOfTopscores()
{
	return NUMBER_OF_TOPSCORES;
}

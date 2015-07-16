/*
 * Levels.cpp
 *
 *  Created on: 16-apr.-2015
 *      Author: Thomas
 */

#include "Levels.h"

using namespace CCG;

Levels::Levels()
{
	levels = new Level*[LEVELS_MAX]();
	initializeLevels();
}

Levels::~Levels()
{
	releaseLevels();
	levels = NULL;
}

Level* Levels::getLevel(int level)
{
	if(level <= LEVELS_MAX && level > 0)
	{
		return levels[level - 1];
	}
	else
	{
		return NULL;
	}
}

int Levels::availableLevels()
{
	return LEVELS_MAX;
}

void Levels::initializeLevels()
{
	levels[0] = new Level01();
	levels[1] = new Level02();
}

void Levels::releaseLevels()
{
	int i;

	for(i = 0; i < LEVELS_MAX; i++)
	{
		delete(levels[i]);
		levels[i] = NULL;
	}
}

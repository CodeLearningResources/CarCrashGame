/*
 * HighscoreEntry.cpp
 *
 *  Created on: 21-jun.-2015
 *      Author: Thomas
 */

#include "HighscoreEntry.h"

using namespace CCG;

HighscoreEntry::HighscoreEntry()
{
	name = "";
	score = 0;
}

HighscoreEntry::HighscoreEntry(std::string name, int score)
{
	this->name = name;
	this->score = score;
}

HighscoreEntry::HighscoreEntry(const HighscoreEntry& entry)
{
	this->name = entry.name;
	this->score = entry.score;
}

HighscoreEntry::~HighscoreEntry()
{

}

void HighscoreEntry::setName(std::string name)
{
	this->name = name;
}

void HighscoreEntry::setScore(int score)
{
	this->score = score;
}

std::string HighscoreEntry::getName()
{
	return this->name;
}

int HighscoreEntry::getScore()
{
	return this->score;
}

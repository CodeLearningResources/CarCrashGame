/*
 * HUD.cpp
 *
 *  Created on: 30-mrt.-2015
 *      Author: Thomas
 */

#include "HUD.h"

using namespace CCG;

HUD::HUD() : GameElement()
{
	numberOfPlayers = 0;
	players = new Player*[MAX_PLAYERS]();
	thisPlayer = 0;
}

HUD::~HUD()
{
	delete(players);
}

void HUD::setPlayer(Player* player, int playerNumber)
{
	if(playerNumber >= 0 && playerNumber < MAX_PLAYERS)
	{
		players[playerNumber] = player;
	}
}

void HUD::setThisPlayer(int playerNumber)
{
	if(playerNumber >= 0 && playerNumber < MAX_PLAYERS)
	{
		this->thisPlayer = playerNumber;
	}
}

Player* HUD::getPlayer(int playerNumber) const
{
	if(playerNumber >= 0 && playerNumber < MAX_PLAYERS)
	{
		return players[playerNumber];
	}
	else
	{
		return NULL;
	}
}

int HUD::getThisPlayer(void) const
{
	return thisPlayer;
}

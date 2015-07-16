/*
 * SDLHUD.cpp
 *
 *  Created on: 30-mrt.-2015
 *      Author: Thomas
 */

#include "SDLHUD.h"

using namespace CCG_SDL;

//Default constructor
SDLHUD::SDLHUD() : CCG::HUD()
{
	this->visibility = false;
	this->statusbarTexture = NULL;
	this->healthbarTexture = NULL;
	this->nitrobarTexture = NULL;
	this->invincibilityTexture = NULL;
	this->playerStatusTexture = NULL;
	this->rocketTexture = NULL;
	this->nameText = NULL;
	this->scoreText = NULL;
	this->rocketsText = NULL;
	this->renderer = NULL;
}

SDLHUD::SDLHUD(SDL_Renderer* renderer, SDLTexture** texturePack, SDLText* nameText, SDLText* scoreText, SDLText* rocketsText) : CCG::HUD()
{
	this->visibility = false;
	this->statusbarTexture = texturePack[HUD_ELEMENT_STATUSBAR];
	this->healthbarTexture = texturePack[HUD_ELEMENT_HEALTHBAR];
	this->nitrobarTexture = texturePack[HUD_ELEMENT_NITROBAR];
	this->invincibilityTexture = texturePack[HUD_ELEMENT_INVINCIBILITY_STATUS];
	this->playerStatusTexture = new SDLTexture*[MAX_PLAYERS]();
	this->playerStatusTexture[0] = texturePack[HUD_ELEMENT_PLAYER01_STATUS];
	this->playerStatusTexture[1] = texturePack[HUD_ELEMENT_PLAYER02_STATUS];
	this->playerStatusTexture[2] = texturePack[HUD_ELEMENT_PLAYER03_STATUS];
	this->playerStatusTexture[3] = texturePack[HUD_ELEMENT_PLAYER04_STATUS];
	this->rocketTexture = texturePack[HUD_ELEMENT_ROCKETS];
	this->nameText = nameText;
	this->nameText->setColor(255, 255, 255, 0);
	this->nameText->visible(true);
	this->scoreText = scoreText;
	this->scoreText->setColor(255, 255, 255, 0);
	this->scoreText->visible(true);
	this->rocketsText = rocketsText;
	this->rocketsText->setColor(255, 255, 255, 0);
	this->rocketsText->visible(true);
	this->renderer = renderer;
}

//Destructor
SDLHUD::~SDLHUD()
{
	//Destruct SDLHUD object
	if(nameText)
		delete(nameText);

	if(scoreText)
		delete(scoreText);
}

void SDLHUD::visible(bool flag)
{
	this->visibility = flag;
}

bool SDLHUD::isVisible()
{
	return this->visibility;
}

void SDLHUD::update()
{
	int i;
	char score[25];
	char rockets[9];

	if(statusbarTexture == NULL || healthbarTexture == NULL || nitrobarTexture == NULL)
	{
		return;
	}

	if(visibility)
	{
		if(getPlayer(getThisPlayer()) != NULL)
		{
			int healthYSize = 103 * (getPlayer(getThisPlayer())->getPlayerCar()->getHealth() / 100.f);
			int nitroYSize = 94 * (getPlayer(getThisPlayer())->getPlayerCar()->getNitro() / 100.f);

			SDL_Rect renderBoxStatus = {(int)getPosX() + 10, (int)getPosY() + 568, 140, 200};
			SDL_RenderCopyEx(renderer, statusbarTexture->getTexture(), NULL, &renderBoxStatus, 0, NULL, SDL_FLIP_NONE);

			SDL_Rect renderBoxHealth = {(int)getPosX() + 10 + 27 , (int)getPosY() + 568 + 13 + 103 - healthYSize, 26, healthYSize};
			SDL_RenderCopyEx(renderer, healthbarTexture->getTexture(), NULL, &renderBoxHealth, 0, NULL, SDL_FLIP_NONE);

			SDL_Rect renderBoxNitro = {(int)getPosX() + 10 + 58, (int)getPosY() + 568 + 34 + 94 - nitroYSize, 22, nitroYSize};
			SDL_RenderCopyEx(renderer, nitrobarTexture->getTexture(), NULL, &renderBoxNitro, 0, NULL, SDL_FLIP_NONE);

			SDL_Rect renderBoxRocketIcon = {(int)getPosX() + 105, (int)getPosY() + 645, 12, 26};
			SDL_RenderCopyEx(renderer, rocketTexture->getTexture(), NULL, &renderBoxRocketIcon, 30, NULL, SDL_FLIP_NONE);

			sprintf(rockets, "%d", (int)getPlayer(getThisPlayer())->getRockets());
			rocketsText->setText(rockets);
			rocketsText->setPos((int)getPosX() + 125, (int)getPosY() + 645);
			rocketsText->update();

			if(getPlayer(getThisPlayer())->getPlayerCar()->isInvincible())
			{
				SDL_Rect renderBoxInvincibility = {(int)getPosX() + 104, (int)getPosY() + 684, 20, 20};
				SDL_RenderCopyEx(renderer, invincibilityTexture->getTexture(), NULL, &renderBoxInvincibility, 0, NULL, SDL_FLIP_NONE);
			}
		}

		for(i = 0; i < 4; i++)
		{
			if(getPlayer(i) != NULL)
			{
				int scoreXPos = 40 + (i * 250);

				SDL_Rect renderBoxScore = {(int)getPosX() + scoreXPos, (int)getPosY() + 10, 200, 50};
				SDL_RenderCopyEx(renderer, playerStatusTexture[i]->getTexture(), NULL, &renderBoxScore, 0, NULL, SDL_FLIP_NONE);

				nameText->setText(getPlayer(i)->getName());
				nameText->setPos(scoreXPos + 5, 12);
				nameText->update();

				sprintf(score, "%d", (int)getPlayer(i)->getScore());
				scoreText->setText(score);
				scoreText->setPos(scoreXPos + 5, 44);
				scoreText->update();
			}
		}
	}
}


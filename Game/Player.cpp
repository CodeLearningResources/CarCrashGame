/*
 * Player.cpp
 *
 *  Created on: 4-apr.-2015
 *      Author: Thomas
 */

#include "Player.h"

using namespace CCG;

Player::Player()
{
	name = "player";
	score = 0.0f;
	rockets = 0;
	playerCar = NULL;
	fireRocket = false;
	rocketFired = false;
	controls = new KeyboardKey*[PLAYER_CONTROL_MAX]();

	for(int i = 0; i < PLAYER_CONTROL_MAX; i++)
	{
		controls[i] = new KeyboardKey();
	}

	initializeControls(0);
}

Player::Player(std::string name, int controlMacro)
{
	this->name = name;
	this->score = 0.0f;
	this->rockets = 0;
	this->playerCar = NULL;
	this->fireRocket = false;
	this->rocketFired = false;
	this->controls = new KeyboardKey*[PLAYER_CONTROL_MAX]();

	for(int i = 0; i < PLAYER_CONTROL_MAX; i++)
	{
		controls[i] = new KeyboardKey();
	}

	initializeControls(controlMacro);
}

Player::~Player()
{
	if(playerCar)
		delete(playerCar);

	for(int i = 0; i < PLAYER_CONTROL_MAX; i++)
	{
		delete(controls[i]);
		controls[i] = NULL;
	}

	delete(controls);
	controls = NULL;
}

void Player::initializeControls(int macro)
{
	switch(macro)
	{
		case 1:
			controls[PLAYER_CONTROL_UP]->setKeyValue(KEY_UP);
			controls[PLAYER_CONTROL_RIGHT]->setKeyValue(KEY_RIGHT);
			controls[PLAYER_CONTROL_DOWN]->setKeyValue(KEY_DOWN);
			controls[PLAYER_CONTROL_LEFT]->setKeyValue(KEY_LEFT);
			//controls[PLAYER_CONTROL_NITRO]->setKeyValue(KEY_SPACE);
			controls[PLAYER_CONTROL_ROCKET]->setKeyValue(KEY_R);
			break;
		default:
			controls[PLAYER_CONTROL_UP]->setKeyValue(KEY_Z);
			controls[PLAYER_CONTROL_RIGHT]->setKeyValue(KEY_D);
			controls[PLAYER_CONTROL_DOWN]->setKeyValue(KEY_S);
			controls[PLAYER_CONTROL_LEFT]->setKeyValue(KEY_Q);
			//controls[PLAYER_CONTROL_NITRO]->setKeyValue(KEY_SPACE);
			controls[PLAYER_CONTROL_ROCKET]->setKeyValue(KEY_R);
			break;
	}
}

void Player::handleEvent(Event* event)
{
	if(event != NULL && playerCar != NULL)
	{
		if(event->getType() == KEYBOARD_EVENT)
		{
			if(event->getKeyEvent()->getKeyValue() == controls[PLAYER_CONTROL_UP]->getKeyValue())
			{
				if(event->getButtonState() == BUTTON_PRESSED)
				{
					playerCar->goUp(true);
				}
				else
				{
					playerCar->goUp(false);
				}
			}
			else if(event->getKeyEvent()->getKeyValue() == controls[PLAYER_CONTROL_RIGHT]->getKeyValue())
			{
				if(event->getButtonState() == BUTTON_PRESSED)
				{
					playerCar->goRight(true);
				}
				else
				{
					playerCar->goRight(false);
				}
			}
			else if(event->getKeyEvent()->getKeyValue() == controls[PLAYER_CONTROL_DOWN]->getKeyValue())
			{
				if(event->getButtonState() == BUTTON_PRESSED)
				{
					playerCar->goDown(true);
				}
				else
				{
					playerCar->goDown(false);
				}
			}
			else if(event->getKeyEvent()->getKeyValue() == controls[PLAYER_CONTROL_LEFT]->getKeyValue())
			{
				if(event->getButtonState() == BUTTON_PRESSED)
				{
					playerCar->goLeft(true);
				}
				else
				{
					playerCar->goLeft(false);
				}
			}
			else if(event->getKeyEvent()->getKeyValue() == controls[PLAYER_CONTROL_ROCKET]->getKeyValue())
			{
				if(event->getButtonState() == BUTTON_PRESSED)
				{
					if(!rocketFired)
					{
						if(rockets > 0)
						{
							this->rockets--;
							setFiring(true);
						}
					}

					rocketFired = true;
				}
				else
				{
					rocketFired = false;
				}
			}
		}
	}
}

KeyboardKey** Player::getControls()
{
	return this->controls;
}

void Player::setControls(KeyboardKey** controls)
{
	for(int i = 0; i < PLAYER_CONTROL_MAX; i++)
	{
		*this->controls[i] = *controls[i];
	}
}

void Player::setName(std::string name)
{
	this->name = name;
}

void Player::setScore(float points)
{
	this->score = points;
}

void Player::setCar(Car* playerCar)
{
	if(this->playerCar)
		delete(this->playerCar);

	this->playerCar = playerCar;
}

void Player::setHealth(int points)
{
	if(playerCar != NULL)
	{
		playerCar->setHealth(points);
	}
}

void Player::setNitro(int points)
{
	if(playerCar != NULL)
	{
		playerCar->setNitro(points);
	}
}

void Player::setRockets(int rockets)
{
	this->rockets = rockets;
}

void Player::setFiring(bool flag)
{
	this->fireRocket = flag;
}

std::string Player::getName()
{
	return name;
}

float Player::getScore()
{
	return score;
}

Car* Player::getPlayerCar()
{
	return playerCar;
}

int Player::getHealth()
{
	if(playerCar != NULL)
	{
		return playerCar->getHealth();
	}
	else
	{
		return -1;
	}
}

int Player::getNitro()
{
	if(playerCar != NULL)
	{
		return playerCar->getNitro();
	}
	else
	{
		return -1;
	}
}

int Player::getRockets()
{
	return this->rockets;
}

bool Player::isAlive()
{
	if(this->playerCar != NULL)
	{
		return this->playerCar->isAlive();
	}
	else
	{
		return false;
	}
}

bool Player::isFiring()
{
	return fireRocket;
}

void Player::addScore(float points)
{
	this->score += points;
}

void Player::addRockets(int rockets)
{
	this->rockets += rockets;
}

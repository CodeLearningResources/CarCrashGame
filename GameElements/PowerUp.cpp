/*
 * PowerUp.cpp
 *
 *  Created on: 19-apr.-2015
 *      Author: Thomas
 */

#include "PowerUp.h"

using namespace CCG;

PowerUp::PowerUp() : GameElement()
{
	this->bonus = POWERUP_BONUS_HEALTH;
	this->bonusValue = 0;
	this->available = true;
}

PowerUp::PowerUp(PowerUpBonus bonus) : GameElement()
{
	this->bonus = bonus;
	this->bonusValue = 0;
	this->available = true;
}

PowerUp::PowerUp(const PowerUp& powerUp) : GameElement(powerUp)
{
	this->bonus = powerUp.bonus;
	this->bonusValue = powerUp.bonusValue;
	this->available = powerUp.available;
}

PowerUp::~PowerUp()
{

}

PowerUpBonus PowerUp::getBonusType()
{
	return this->bonus;
}

bool PowerUp::isAvailable()
{
	return this->available;
}

int PowerUp::getBonusValue()
{
	return this->bonusValue;
}

void PowerUp::setBonusValue(int bonusValue)
{
	this->bonusValue = bonusValue;
}

void PowerUp::setAvailability(bool flag)
{
	this->available = flag;
}

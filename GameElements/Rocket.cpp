/*
 * Rocket.cpp
 *
 *  Created on: 8-jun.-2015
 *      Author: Thomas
 */

#include "Rocket.h"

using namespace CCG;

Rocket::Rocket() : GameElement()
{
	hitPoints = 0;
	speed = 0.0f;
	direction = DIRECTION_UP;
	alive = true;
	owner = NULL;
}

Rocket::Rocket(int hitPoints, float speed, Direction direction, Player* owner) : GameElement()
{
	float velX = 0.0f;
	float velY = 0.0f;

	this->hitPoints = hitPoints;
	this->speed = speed;
	this->direction = direction;
	this->alive = true;
	this->owner = owner;

	float rotation = 0.0f;

	switch(direction)
	{
		case DIRECTION_UP:
			rotation = 0.0f;
			velY = -speed;
			break;
		case DIRECTION_RIGHT:
			rotation = 90.0f;
			velX = speed;
			break;
		case DIRECTION_DOWN:
			rotation = 180.0f;
			velY = speed;
			break;
		case DIRECTION_LEFT:
			rotation = 270.0f;
			velX = -speed;
			break;
	}

	setRotation(rotation);
	setVelocity(velX, velY);
}

Rocket::Rocket(const Rocket& rocket) : GameElement(rocket)
{
	float velX = 0.0f;
	float velY = 0.0f;

	this->hitPoints = rocket.hitPoints;
	this->speed = rocket.speed;
	this->direction = rocket.direction;
	this->alive = rocket.alive;
	this->owner = rocket.owner;

	float rotation = 0.0f;

	switch(direction)
	{
		case DIRECTION_UP:
			rotation = 0.0f;
			velY = -speed;
			break;
		case DIRECTION_RIGHT:
			rotation = 90.0f;
			velX = speed;
			break;
		case DIRECTION_DOWN:
			rotation = 180.0f;
			velY = speed;
			break;
		case DIRECTION_LEFT:
			rotation = 270.0f;
			velX = -speed;
			break;
	}

	setRotation(rotation);
	setVelocity(velX, velY);
}

Rocket::~Rocket()
{

}

int Rocket::getHitPoints()
{
	return this->hitPoints;
}

float Rocket::getSpeed()
{
	return this->speed;
}

Direction Rocket::getDirection()
{
	return this->direction;
}

Player* Rocket::getOwner()
{
	return this->owner;
}

bool Rocket::isAlive()
{
	return this->alive;
}

void Rocket::setHitPoints(int hitPoints)
{
	this->hitPoints = hitPoints;
}

void Rocket::setSpeed(float speed)
{
	float velX = 0.0f;
	float velY = 0.0f;

	this->speed = speed;

	switch(getDirection())
	{
		case DIRECTION_UP:
			velY = -speed;
			break;
		case DIRECTION_RIGHT:
			velX = speed;
			break;
		case DIRECTION_DOWN:
			velY = speed;
			break;
		case DIRECTION_LEFT:
			velX = -speed;
			break;
	}

	setVelocity(velX, velY);
}

void Rocket::setDirection(Direction direction)
{
	float rotation = 0.0f;

	this->direction = direction;

	switch(direction)
	{
		case DIRECTION_UP:
			rotation = 0.0f;
			break;
		case DIRECTION_RIGHT:
			rotation = 90.0f;
			break;
		case DIRECTION_DOWN:
			rotation = 180.0f;
			break;
		case DIRECTION_LEFT:
			rotation = 270.0f;
			break;
	}

	setRotation(rotation);
}

void Rocket::setAlive(bool flag)
{
	this->alive = flag;
}

void Rocket::setOwner(Player* owner)
{
	this->owner = owner;
}

/*
 * Car.cpp
 *
 *  Created on: 9-mrt.-2015
 *      Author: Thomas
 */

#include "Car.h"

using namespace CCG;

//Default constructor
Car::Car() : GameElement()
{
	health = 100;
	nitro = 100;
	invincibleTime = 0.0f;

	moveToX = 0.0f;
	moveToY = 0.0f;

	moveToFlag = false;

	alive = true;

	direction = DIRECTION_UP;

	left = false;
	right = false;
	up = false;
	down = false;
}

//Constructor
Car::Car(int health, int nitro) : GameElement()
{
	this->health = health;
	this->nitro = nitro;
	this->invincibleTime = 0.0f;

	this->moveToX = 0.0f;
	this->moveToY = 0.0f;

	this->moveToFlag = false;

	this->alive = true;

	this->direction = DIRECTION_UP;

	left = false;
	right = false;
	up = false;
	down = false;
}

Car::Car(const Car& car) : GameElement(car)
{
	this->health = car.health;
	this->nitro = car.nitro;
	this->invincibleTime = car.invincibleTime;

	this->moveToX = car.moveToX;
	this->moveToY = car.moveToY;

	this->moveToFlag = car.moveToFlag;

	this->alive = car.alive;

	this->direction = car.direction;

	left = false;
	right = false;
	up = false;
	down = false;
}

//Destructor
Car::~Car()
{
	//Destruct Car object
}

Direction Car::getDriveDirection() const
{
	return this->direction;
}

int Car::getHealth() const
{
	return this->health;
}

int Car::getNitro() const
{
	return this->nitro;
}

float Car::getInvincibleTime() const
{
	return this->invincibleTime;
}

bool Car::isInvincible() const
{
	if(this->invincibleTime > 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Car::isAlive() const
{
	return this->alive;
}

void Car::setDriveDirection(Direction direction)
{
	float rotation = 0.0f;

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

	this->setRotation(rotation);
	this->direction = direction;
}

void Car::setHealth(int points)
{
	this->health = points;
}

void Car::setNitro(int points)
{
	this->nitro = nitro;
}

void Car::setInvincibleTime(float time)
{
	this->invincibleTime = time;
}

void Car::setAlive(bool flag)
{
	this->alive = flag;
}

void Car::heal(int points)
{
	this->health += points;

	if(this->health > 100)
	{
		this->health = 100;
	}
}

void Car::hit(int points)
{
	this->health -= points;

	if(this->health <= 0)
	{
		this->health = 0;
		this->alive = false;
	}
}

void Car::goLeft(bool flag)
{
	this->left = flag;
}

void Car::goRight(bool flag)
{
	this->right = flag;
}

void Car::goUp(bool flag)
{
	this->up = flag;
}

void Car::goDown(bool flag)
{
	this->down = flag;
}

void Car::stopMovement()
{
	this->left = false;
	this->right = false;
	this->up = false;
	this->down = false;
}

void Car::moveToLocation(float x, float y, bool flag)
{
	this->moveToX = x;
	this->moveToY = y;
	this->moveToFlag = flag;

	this->left = false;
	this->right = false;
	this->up = false;
	this->down = false;
}

void Car::keepInLevelBoundaries(int x, int y, int width, int height)
{
	if(getPosX() <= x)
	{
		setPosX(x);
		goLeft(false);
	}

	if((getPosX() + getSizeX()) >= width)
	{
		setPosX(width - getSizeX());
		goRight(false);
	}

	if(getPosY() <= y)
	{
		setPosY(y);
		goUp(false);
	}

	if((getPosY() + getSizeY()) >= height)
	{
		setPosY(height - getSizeY());
		goDown(false);
	}
}

void Car::move(float timeStep)
{
	float posX = getPosX();
	float posY = getPosY();
	float velX = getVelX();
	float velY = getVelY();
	float relRotation = getRelRotation();
	float velRot = getRotVelocity();
	float sizeX, sizeY;

	//Automatic move-to procedure
	if(moveToFlag)
	{
		sizeX = getSizeX();
		sizeY = getSizeY();

		if(moveToX < posX + sizeX/2)
		{
			left = true;
			right = false;
		}
		else if(moveToX > posX + sizeX/2)
		{
			right = true;
			left = false;
		}
		else
		{
			right = false;
			left = false;
		}

		if(moveToY < posY + sizeY/2)
		{
			up = true;
			down = false;
		}
		else if(moveToY > posY + sizeY/2)
		{
			down = true;
			up = false;
		}
		else
		{
			down = false;
			up = false;
		}
	}

	//Move car procedure
	if(left && !right)
	{
		posX -= velX * timeStep;

		if(direction == DIRECTION_UP)
		{
			relRotation -= velRot * timeStep;

			if(relRotation < -CAR_TURN_ROTATION_MAX)
			{
				relRotation = -CAR_TURN_ROTATION_MAX;
			}
		}
		else if(direction == DIRECTION_DOWN)
		{
			relRotation += velRot * timeStep;

			if(relRotation > CAR_TURN_ROTATION_MAX)
			{
				relRotation = CAR_TURN_ROTATION_MAX;
			}
		}
	}
	else if(right && !left)
	{
		posX += velX * timeStep;

		if(direction == DIRECTION_UP)
		{
			relRotation += velRot * timeStep;

			if(relRotation > CAR_TURN_ROTATION_MAX)
			{
				relRotation = CAR_TURN_ROTATION_MAX;
			}
		}
		else if(direction == DIRECTION_DOWN)
		{
			relRotation -= velRot * timeStep;

			if(relRotation < -CAR_TURN_ROTATION_MAX)
			{
				relRotation = -CAR_TURN_ROTATION_MAX;
			}
		}
	}
	else
	{
		if(direction == DIRECTION_UP || direction == DIRECTION_DOWN)
		{
			if(relRotation < 0)
			{
				relRotation += velRot * timeStep;

				if(relRotation > 0)
				{
					relRotation = 0;
				}
			}
			else if(relRotation > 0)
			{
				relRotation -= velRot * timeStep;

				if(relRotation < 0)
				{
					relRotation = 0;
				}
			}
		}
	}

	if(up && !down)
	{
		posY -= velY * timeStep;

		if(direction == DIRECTION_LEFT)
		{
			relRotation += velRot * timeStep;

			if(relRotation > CAR_TURN_ROTATION_MAX)
			{
				relRotation = CAR_TURN_ROTATION_MAX;
			}
		}
		else if(direction == DIRECTION_RIGHT)
		{
			relRotation -= velRot * timeStep;

			if(relRotation < -CAR_TURN_ROTATION_MAX)
			{
				relRotation = -CAR_TURN_ROTATION_MAX;
			}
		}
	}
	else if(down && !up)
	{
		posY += velY * timeStep;

		if(direction == DIRECTION_LEFT)
		{
			relRotation -= velRot * timeStep;

			if(relRotation < -CAR_TURN_ROTATION_MAX)
			{
				relRotation = -CAR_TURN_ROTATION_MAX;
			}
		}
		else if(direction == DIRECTION_RIGHT)
		{
			relRotation += velRot * timeStep;

			if(relRotation > CAR_TURN_ROTATION_MAX)
			{
				relRotation = CAR_TURN_ROTATION_MAX;
			}
		}
	}
	else
	{
		if(direction == DIRECTION_LEFT || direction == DIRECTION_RIGHT)
		{
			if(relRotation < 0)
			{
				relRotation += velRot * timeStep;

				if(relRotation > 0)
				{
					relRotation = 0;
				}
			}
			else if(relRotation > 0)
			{
				relRotation -= velRot * timeStep;

				if(relRotation < 0)
				{
					relRotation = 0;
				}
			}
		}
	}

	setPos(posX, posY);
	setRelRotation(relRotation);
}

void Car::updateStatus(float timeStep)
{
	this->invincibleTime -= timeStep;

	if(this->invincibleTime < 0.0f)
	{
		this->invincibleTime = 0.0f;
	}
}

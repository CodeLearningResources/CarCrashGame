/*
 * GameElement.cpp
 *
 *  Created on: 15-mrt.-2015
 *      Author: Thomas
 */

#include "GameElement.h"

using namespace CCG;

GameElement::GameElement()
{
	posX = 0;
	posY = 0;
	sizeX = 0;
	sizeY = 0;
	colliderPosX = 0;
	colliderPosY = 0;
	colliderSizeX = 0;
	colliderSizeY = 0;
	velX = 0;
	velY = 0;
	rotation = 0;
	relRotation = 0;
	velRot = 0;
}

GameElement::GameElement(const GameElement& gameElement)
{
	this->posX = gameElement.posX;
	this->posY = gameElement.posY;
	this->sizeX = gameElement.sizeX;
	this->sizeY = gameElement.sizeY;
	this->colliderPosX = gameElement.colliderPosX;
	this->colliderPosY = gameElement.colliderPosY;
	this->colliderSizeX = gameElement.colliderSizeX;
	this->colliderSizeY = gameElement.colliderSizeY;
	this->velX = gameElement.velX;
	this->velY = gameElement.velY;
	this->rotation = gameElement.rotation;
	this->relRotation = gameElement.relRotation;
	this->velRot = gameElement.velRot;
}

GameElement::~GameElement()
{
	//Destruct GameElement object
}

void GameElement::setSize(float sizeX, float sizeY)
{
	this->sizeX = sizeX;
	this->sizeY = sizeY;
}

void GameElement::setPos(float posX, float posY)
{
	this->posX = posX;
	this->posY = posY;
}

void GameElement::setCollider(float posX, float posY, float sizeX, float sizeY)
{
	this->colliderPosX = posX;
	this->colliderPosY = posY;
	this->colliderSizeX = sizeX;
	this->colliderSizeY = sizeY;
}

void GameElement::setVelocity(float velX, float velY)
{
	this->velX = velX;
	this->velY = velY;
}

void GameElement::setRotation(float rotation)
{
	this->rotation = rotation;
}

void GameElement::setRelRotation(float rotation)
{
	this->relRotation = rotation;
}

void GameElement::setRotVelocity(float velRot)
{
	this->velRot = velRot;
}

void GameElement::setPosX(float posX)
{
	this->posX = posX;
}

void GameElement::setPosY(float posY)
{
	this->posY = posY;
}

void GameElement::setVelX(float velX)
{
	this->velX = velX;
}

void GameElement::setVelY(float velY)
{
	this->velY = velY;
}

float GameElement::getSizeX() const
{
	return this->sizeX;
}

float GameElement::getSizeY() const
{
	return this->sizeY;
}

float GameElement::getPosX() const
{
	return this->posX;
}

float GameElement::getPosY() const
{
	return this->posY;
}

float GameElement::getVelX() const
{
	return this->velX;
}

float GameElement::getVelY() const
{
	return this->velY;
}

float GameElement::getRotation() const
{
	return this->rotation;
}

float GameElement::getColliderPosX() const
{
	return this->colliderPosX;
}

float GameElement::getColliderPosY() const
{
	return this->colliderPosY;
}

float GameElement::getColliderSizeX() const
{
	return this->colliderSizeX;
}

float GameElement::getColliderSizeY() const
{
	return this->colliderSizeY;
}

float GameElement::getRelRotation() const
{
	return this->relRotation;
}

float GameElement::getRotVelocity() const
{
	return this->velRot;
}

bool GameElement::checkInBoundaries(int x, int y, int width, int height)
{
	bool inBound = true;

	if(this->posX < x)
	{
		inBound = false;
	}
	else if(this->posY < y)
	{
		inBound = false;
	}
	else if(this->posX + this->sizeX > x + width)
	{
		inBound = false;
	}
	else if(this->posY + this->sizeY > y + height)
	{
		inBound = false;
	}

	return inBound;
}

bool GameElement::checkCollision(GameElement* object)
{
	float leftThis, leftObject;
	float rightThis, rightObject;
	float topThis, topObject;
	float bottomThis, bottomObject;

	if(this == object || object == NULL)
	{
		return false;
	}

	//This or object is not suitable for collision detection
	if((this->colliderSizeX == 0 && this->colliderSizeY == 0) || (object->getColliderSizeX() == 0 && object->getColliderSizeY() == 0))
	{
		return false;
	}

	leftThis = posX + colliderPosX;
	rightThis = posX + colliderPosX + colliderSizeX;
	topThis = posY + colliderPosY;
	bottomThis = posY + colliderPosY + colliderSizeY;

	leftObject = object->getPosX() + object->getColliderPosX();
	rightObject = object->getPosX() + object->getColliderPosX() + object->getColliderSizeX();
	topObject = object->getPosY() + object->getColliderPosY();
	bottomObject = object->getPosY() + object->getColliderPosY() + object->getColliderSizeY();

	if(bottomThis <= topObject)
	{
		return false;
	}

	if(topThis >= bottomObject)
	{
		return false;
	}

	if(rightThis <= leftObject)
	{
		return false;
	}

	if(leftThis >= rightObject)
	{
		return false;
	}

	return true;
}

bool GameElement::checkIntersection(int posX, int posY)
{
	bool intersecting = true;

	if(posX < this->getPosX())
	{
		intersecting = false;
	}
	else if(posX > this->getPosX() + this->getSizeX())
	{
		intersecting = false;
	}
	else if(posY < this->getPosY())
	{
		intersecting = false;
	}
	else if(posY > this->getPosY() + this->getSizeY())
	{
		intersecting = false;
	}

	return intersecting;
}

void GameElement::move(float timeStep)
{
	posX += velX * timeStep;
	posY += velY * timeStep;
	rotation = fmod((rotation + (velRot * timeStep)), 360);
}

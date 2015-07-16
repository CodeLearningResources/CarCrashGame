/*
 * SpawnPoint.cpp
 *
 *  Created on: 14-apr.-2015
 *      Author: Thomas
 */

#include "SpawnPoint.h"

using namespace CCG;

SpawnPoint::SpawnPoint()
{
	posX = 0;
	posY = 0;
	spawnDirection = DIRECTION_DOWN;
	moveSpeed = 0;
	spawnBoxSize = 0;
	spawnDelay = 0;
	spawnDelayOffset = 0;
	spawnDelayAcceleration = 0;
	nextSpawn = -1;
	objectQueue = NULL;
	spawnTimer = NULL;
}

SpawnPoint::SpawnPoint(int posX, int posY, Direction spawnDirection, float moveSpeed, int spawnBoxSize, float spawnDelay, float spawnDelayOffset)
{
	this->posX = posX;
	this->posY = posY;
	this->spawnDirection = spawnDirection;
	this->moveSpeed = moveSpeed;
	this->spawnBoxSize = spawnBoxSize;
	this->spawnDelay = spawnDelay;
	this->spawnDelayOffset = spawnDelayOffset;
	this->spawnDelayAcceleration = 0;
	this->nextSpawn = -1;
	this->objectQueue = NULL;
	this->spawnTimer = NULL;
}

SpawnPoint::SpawnPoint(const SpawnPoint& spawnPoint)
{
	this->posX = spawnPoint.posX;
	this->posY = spawnPoint.posY;
	this->spawnDirection = spawnPoint.spawnDirection;
	this->moveSpeed = spawnPoint.moveSpeed;
	this->spawnBoxSize = spawnPoint.spawnBoxSize;
	this->spawnDelay = spawnPoint.spawnDelay;
	this->spawnDelayOffset = spawnPoint.spawnDelayOffset;
	this->spawnDelayAcceleration = spawnPoint.spawnDelayAcceleration;
	this->nextSpawn = spawnPoint.nextSpawn;
	this->objectQueue = NULL;
	this->spawnTimer = NULL;
}

SpawnPoint::~SpawnPoint()
{
	if(objectQueue)
	{
		delete(objectQueue);
	}

	if(spawnTimer)
	{
		delete(spawnTimer);
	}
}

void SpawnPoint::initialize(Timer* spawnTimer)
{
	this->spawnTimer = spawnTimer;
	this->objectQueue = new std::list<GameElement*>();
	this->spawnDelayAcceleration = 0;
}

void SpawnPoint::setSpawnDelayAcceleration(float accelerationTime)
{
	this->spawnDelayAcceleration = accelerationTime;
}

Direction SpawnPoint::getSpawnDirection()
{
	return this->spawnDirection;
}

float SpawnPoint::getMoveSpeed()
{
	return this->moveSpeed;
}

void SpawnPoint::queueObject(GameElement* object)
{
	objectQueue->push_back(object);
}

void SpawnPoint::spawnObject(GameElement* object)
{
	float objectPosX, objectPosY;
	float spawnOffset;

	if(spawnBoxSize != 0)
	{
		spawnOffset = (rand() % spawnBoxSize) - spawnBoxSize/2;
	}
	else
	{
		spawnOffset = 0;
	}

	switch(spawnDirection)
	{
		case DIRECTION_UP:
			objectPosY = posY;
			objectPosX = posX - object->getSizeX()/2 + spawnOffset;
			break;
		case DIRECTION_DOWN:
			objectPosY = posY - object->getSizeY();
			objectPosX = posX - object->getSizeX()/2 + spawnOffset;
			break;
		case DIRECTION_RIGHT:
			objectPosX = posX - object->getSizeX();
			objectPosY = posY - object->getSizeY()/2 + spawnOffset;
			break;
		case DIRECTION_LEFT:
			objectPosX = posX;
			objectPosY = posY - object->getSizeY()/2 + spawnOffset;
			break;
	}

	object->setPos(objectPosX, objectPosY);
	object->visible(true);
}

void SpawnPoint::clearQueue()
{
	while(!objectQueue->empty())
	{
		objectQueue->pop_front();
	}
}

void SpawnPoint::start()
{
	spawnTimer->start();
}

void SpawnPoint::pause()
{
	spawnTimer->pause();
}

void SpawnPoint::update()
{
	float lastSpawnTime = spawnTimer->getTicks() / 1000.0f;

	if(nextSpawn == -1)
	{
		//Calculate a new spawn time
		if(spawnDelayOffset != 0)
		{
			nextSpawn = spawnDelay - spawnDelayAcceleration + (rand() % (int)(spawnDelayOffset*100))/100;
		}
		else
		{
			nextSpawn = spawnDelay - spawnDelayAcceleration;
		}

		if(nextSpawn < 0)
		{
			nextSpawn = 0;
		}
	}

	if(lastSpawnTime > nextSpawn)
	{
		//Spawn new object if available
		if(!objectQueue->empty())
		{
			GameElement* object = objectQueue->front();

			if(object != NULL)
			{
				spawnObject(object);
			}

			objectQueue->pop_front();
		}

		nextSpawn = -1;
		spawnTimer->reset();
	}
}

void SpawnPoint::cancelNextSpawn()
{
	if(!objectQueue->empty())
	{
		objectQueue->pop_front();
	}

	spawnTimer->reset();
}

bool SpawnPoint::isEmpty()
{
	return objectQueue->empty();
}

GameElement* SpawnPoint::getNextObject()
{
	if(!objectQueue->empty())
	{
		return objectQueue->front();
	}
	else
	{
		return NULL;
	}
}

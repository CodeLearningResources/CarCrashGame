/*
 * Level.cpp
 *
 *  Created on: 6-apr.-2015
 *      Author: Thomas
 */

#include "Level.h"

using namespace CCG;

Level::Level()
{
	levelIndex = -1;
	levelName = "";
	roundTime = 0.0f;
	mapType = BACKGROUND_MAP_CITY;
	difficulty = 0;

	boundaryX = 0;
	boundaryY = 0;
	boundaryWidth = 0;
	boundaryHeight = 0;
	levelDirection = DIRECTION_UP;

	backgroundSizeX = 0.0f;
	backgroundSizeY = 0.0f;

	startGameSpeed = 0.0f;
	accelerationGameSpeed = 0.0f;
	maxAccelerationGameSpeed = 0.0f;

	enemySpawnAccelerationTime = 0.0f;
	enemySpawnMaxAccelerationTime = 0.0f;

	playerSpawnPoint = NULL;
	startLocationX = 0;
	startLocationY = 0;

	enemyMaxEntities = 0;

	enemySpawnPoints = 0;
	enemySpawners = NULL;

	powerUpSpawnPoints = 0;
	powerUpSpawnerType = NULL;
	powerUpSpawners = NULL;

	powerUpHealthBonus = 0;
	powerUpNitroBonus = 0;
	powerUpPointsBonus = 0;
	powerUpInvincibilityBonus = 0;
	powerUpRocketsBonus = 0;

	startRockets = 0;
	rocketSpeed = 0.0f;
	rocketDamage = 0;

	survivalPoints = 0;
	rocketHitPoints = 0;
	carDestroyedPoints = 0;
}

Level::Level(const Level& level)
{
	this->levelIndex = level.levelIndex;
	this->levelName = level.levelName;
	this->roundTime = level.roundTime;
	this->mapType = level.mapType;
	this->difficulty = level.difficulty;

	this->boundaryX = level.boundaryX;
	this->boundaryY = level.boundaryY;
	this->boundaryWidth = level.boundaryWidth;
	this->boundaryHeight = level.boundaryHeight;
	this->levelDirection = level.levelDirection;

	this->backgroundSizeX = level.backgroundSizeX;
	this->backgroundSizeY = level.backgroundSizeY;

	this->startGameSpeed = level.startGameSpeed;
	this->accelerationGameSpeed = level.accelerationGameSpeed;
	this->maxAccelerationGameSpeed = level.maxAccelerationGameSpeed;

	this->enemySpawnAccelerationTime = level.enemySpawnAccelerationTime;
	this->enemySpawnMaxAccelerationTime = level.enemySpawnMaxAccelerationTime;

	this->playerSpawnPoint = new SpawnPoint();
	*this->playerSpawnPoint = *level.playerSpawnPoint;
	this->startLocationX = level.startLocationX;
	this->startLocationY = level.startLocationY;

	this->enemyMaxEntities = level.enemyMaxEntities;

	this->enemySpawnPoints = level.enemySpawnPoints;

	if(level.enemySpawnPoints > 0)
		this->enemySpawners = new SpawnPoint*[level.enemySpawnPoints]();

	for(int i = 0; i < level.enemySpawnPoints; i++)
	{
		this->enemySpawners[i] = new SpawnPoint();
		*this->enemySpawners[i] = *level.enemySpawners[i];
	}

	this->powerUpSpawnPoints = level.powerUpSpawnPoints;

	if(level.powerUpSpawnPoints)
	{
		this->powerUpSpawnerType = new PowerUpType[level.powerUpSpawnPoints]();
		this->powerUpSpawners = new SpawnPoint*[level.powerUpSpawnPoints]();
	}

	for(int i = 0; i < level.powerUpSpawnPoints; i++)
	{
		this->powerUpSpawnerType[i] = level.powerUpSpawnerType[i];

		this->powerUpSpawners[i] = new SpawnPoint();
		*this->powerUpSpawners[i] = *level.powerUpSpawners[i];
	}

	this->powerUpHealthBonus = level.powerUpHealthBonus;
	this->powerUpNitroBonus = level.powerUpNitroBonus;
	this->powerUpPointsBonus = level.powerUpPointsBonus;
	this->powerUpInvincibilityBonus = level.powerUpInvincibilityBonus;
	this->powerUpRocketsBonus = level.powerUpRocketsBonus;

	this->startRockets = level.startRockets;
	this->rocketSpeed = level.rocketSpeed;
	this->rocketDamage = level.rocketDamage;

	this->survivalPoints = level.survivalPoints;
	this->rocketHitPoints = level.rocketHitPoints;
	this->carDestroyedPoints = level.carDestroyedPoints;
}

Level::~Level()
{
	int i;

	for(i = 0; i < enemySpawnPoints; i++)
	{
		delete(enemySpawners[i]);
		enemySpawners[i] = NULL;
	}

	for(i = 0; i < powerUpSpawnPoints; i++)
	{
		delete(powerUpSpawners[i]);
		powerUpSpawners[i] = NULL;
	}

	if(enemySpawnPoints > 0)
	{
		delete(enemySpawners);
		enemySpawners = NULL;
	}

	if(powerUpSpawnPoints > 0)
	{
		delete(powerUpSpawnerType);
		powerUpSpawnerType = NULL;

		delete(powerUpSpawners);
		powerUpSpawners = NULL;
	}
}

int Level::getLevelIndex() const
{
	return this->levelIndex;
}

std::string Level::getName() const
{
	return this->levelName;
}

float Level::getRoundTime() const
{
	return this->roundTime;
}

BackgroundType Level::getMap() const
{
	return this->mapType;
}

int Level::getDifficulty() const
{
	return this->difficulty;
}

void Level::getLevelBoundaries(int* x, int* y, int* width, int* height)
{
	*x = this->boundaryX;
	*y = this->boundaryY;
	*width = this->boundaryWidth;
	*height = this->boundaryHeight;
}

void Level::getBackgroundSize(float* x, float* y)
{
	*x = this->backgroundSizeX;
	*y = this->backgroundSizeY;
}

Direction Level::getLevelDirection() const
{
	return this->levelDirection;
}

float Level::getStartGameSpeed() const
{
	return this->startGameSpeed;
}

float Level::getAccelerationGameSpeed() const
{
	return this->accelerationGameSpeed;
}

float Level::getMaxAccelerationGameSpeed() const
{
	return this->maxAccelerationGameSpeed;
}

float Level::getEnemySpawnAccelerationTime() const
{
	return this->enemySpawnAccelerationTime;
}

float Level::getEnemySpawnMaxAccelerationTime() const
{
	return this->enemySpawnMaxAccelerationTime;
}

int Level::getEnemyMaxEntities() const
{
	return this->enemyMaxEntities;
}

int Level::getSurvivalPointsPerSecond() const
{
	return this->survivalPoints;
}

int Level::getRocketHitPoints(void) const
{
	return this->rocketHitPoints;
}

int Level::getCarDestroyedPoints(void) const
{
	return this->carDestroyedPoints;
}

int Level::getEnemySpawnPointsSize() const
{
	return this->enemySpawnPoints;
}

int Level::getPowerUpSpawnPointsSize() const
{
	return this->powerUpSpawnPoints;
}

int Level::getPowerUpBonusValue(PowerUpBonus bonus) const
{
	int bonusValue;

	switch(bonus)
	{
		case POWERUP_BONUS_HEALTH:
			bonusValue = this->powerUpHealthBonus;
			break;
		case POWERUP_BONUS_NITRO:
			bonusValue = this->powerUpNitroBonus;
			break;
		case POWERUP_BONUS_POINTS:
			bonusValue = this->powerUpPointsBonus;
			break;
		case POWERUP_BONUS_INVINCIBILITY:
			bonusValue = this->powerUpInvincibilityBonus;
			break;
		case POWERUP_BONUS_ROCKETS:
			bonusValue = this->powerUpRocketsBonus;
			break;
		default:
			bonusValue = 0;
			break;
	}

	return bonusValue;
}

PowerUpType* Level::getPowerUpSpawnPointsTypes() const
{
	return this->powerUpSpawnerType;
}

SpawnPoint* Level::getPlayerSpawnPoint() const
{
	return this->playerSpawnPoint;
}

void Level::getPlayerStartPoint(float* x, float* y)
{
	*x = this->startLocationX;
	*y = this->startLocationY;
}

SpawnPoint** Level::getEnemySpawnPoints() const
{
	return this->enemySpawners;
}

SpawnPoint** Level::getPowerUpSpawnPoints() const
{
	return this->powerUpSpawners;
}

int Level::getStartRockets(void) const
{
	return this->startRockets;
}

float Level::getRocketSpeed(void) const
{
	return this->rocketSpeed;
}

int Level::getRocketDamage(void) const
{
	return this->rocketDamage;
}

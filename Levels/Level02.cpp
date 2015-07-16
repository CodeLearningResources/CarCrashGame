/*
 * Level02.cpp
 *
 *  Created on: 17-apr.-2015
 *      Author: Thomas
 */

#include "Level02.h"

using namespace CCG;

Level02::Level02() : Level()
{
	this->levelIndex = 1;
	this->levelName = "The Country Side";
	this->mapType = BACKGROUND_MAP_COUNTRYSIDE;
	this->roundTime = 60.0f;
	this->difficulty = 4;

	this->boundaryX = 115;
	this->boundaryY = 105;
	this->boundaryWidth = 945;
	this->boundaryHeight = 645;
	this->levelDirection = DIRECTION_RIGHT;

	this->backgroundSizeX = 1200;
	this->backgroundSizeY = 768;

	this->startGameSpeed = 150;
	this->accelerationGameSpeed = 0.005;
	this->maxAccelerationGameSpeed = 2.2;

	this->enemySpawnAccelerationTime = 0.0005;
	this->enemySpawnMaxAccelerationTime = 0.9;

	this->playerSpawnPoint = new SpawnPoint(0, 384, DIRECTION_RIGHT, 150, 0, 0, 0);
	this->startLocationX = 512;
	this->startLocationY = 384;

	this->enemyMaxEntities = 25;

	this->enemySpawnPoints = 5;

	if(enemySpawnPoints > 0)
		this->enemySpawners = new SpawnPoint*[enemySpawnPoints]();

	this->enemySpawners[0] = new SpawnPoint(1044, 165, DIRECTION_LEFT, 260, 70, 2.5, 1.9);
	this->enemySpawners[1] = new SpawnPoint(1044, 265, DIRECTION_LEFT, 260, 70, 2, 1.2);
	this->enemySpawners[2] = new SpawnPoint(1044, 365, DIRECTION_LEFT, 260, 70, 2.5, 1.8);
	this->enemySpawners[3] = new SpawnPoint(1044, 465, DIRECTION_LEFT, 260, 70, 2.5, 1.9);
	this->enemySpawners[4] = new SpawnPoint(1044, 565, DIRECTION_LEFT, 260, 70, 2, 1.3);

	this->powerUpSpawnPoints = 4;

	if(powerUpSpawnPoints > 0)
		this->powerUpSpawners = new SpawnPoint*[powerUpSpawnPoints]();

	this->powerUpSpawners[0] = new SpawnPoint(1024, 384, DIRECTION_LEFT, 0, 460, 20, 8);
	this->powerUpSpawners[1] = new SpawnPoint(1024, 384, DIRECTION_LEFT, 0, 460, 8, 4);
	this->powerUpSpawners[2] = new SpawnPoint(1024, 384, DIRECTION_LEFT, 0, 460, 35, 10);
	this->powerUpSpawners[3] = new SpawnPoint(1024, 384, DIRECTION_LEFT, 0, 460, 18, 10);

	if(powerUpSpawnPoints > 0)
		this->powerUpSpawnerType = new PowerUpType[powerUpSpawnPoints]();

	this->powerUpSpawnerType[0] = POWERUP_HEALTH;
	this->powerUpSpawnerType[1] = POWERUP_POINTS;
	this->powerUpSpawnerType[2] = POWERUP_INVINCIBILITY;
	this->powerUpSpawnerType[3] = POWERUP_ROCKETS;

	this->powerUpHealthBonus = 25;
	this->powerUpNitroBonus = 0;
	this->powerUpPointsBonus = 3500;
	this->powerUpInvincibilityBonus = 5;
	this->powerUpRocketsBonus = 2;

	this->startRockets = 3;
	this->rocketSpeed = 400;
	this->rocketDamage = 25;

	this->survivalPoints = 250;
	this->rocketHitPoints = 500;
	this->carDestroyedPoints = 1000;
}

Level02::Level02(const Level& level) : Level(level)
{

}


Level02::~Level02()
{

}

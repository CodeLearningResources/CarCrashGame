/*
 * Level01.cpp
 *
 *  Created on: 6-apr.-2015
 *      Author: Thomas
 */

#include "Level01.h"

using namespace CCG;

Level01::Level01() : Level()
{
	this->levelIndex = 0;
	this->levelName = "The Big City";
	this->mapType = BACKGROUND_MAP_CITY;
	this->roundTime = 60.0f;
	this->difficulty = 3;

	this->boundaryX = 55;
	this->boundaryY = 85;
	this->boundaryWidth = 970;
	this->boundaryHeight = 685;
	this->levelDirection = DIRECTION_UP;

	this->backgroundSizeX = 1024;
	this->backgroundSizeY = 1200;

	this->startGameSpeed = 150;
	this->accelerationGameSpeed = 0.005;
	this->maxAccelerationGameSpeed = 2.5;

	this->enemySpawnAccelerationTime = 0.005;
	this->enemySpawnMaxAccelerationTime = 1.4;

	this->playerSpawnPoint = new SpawnPoint(512, 768, DIRECTION_UP, 150, 0, 0, 0);
	this->startLocationX = 512;
	this->startLocationY = 400;

	this->enemyMaxEntities = 25;

	this->enemySpawnPoints = 6;

	if(enemySpawnPoints > 0)
		this->enemySpawners = new SpawnPoint*[enemySpawnPoints]();

	this->enemySpawners[0] = new SpawnPoint(120, 0, DIRECTION_DOWN, 280, 80, 2.5, 2);
	this->enemySpawners[1] = new SpawnPoint(270, 0, DIRECTION_DOWN, 280, 80, 2, 1.5);
	this->enemySpawners[2] = new SpawnPoint(435, 0, DIRECTION_DOWN, 280, 80, 2.5, 2);
	this->enemySpawners[3] = new SpawnPoint(595, -80, DIRECTION_UP, -100, 80, 3.2, 2.2);
	this->enemySpawners[4] = new SpawnPoint(745, -80, DIRECTION_UP, -100, 80, 3, 2.5);
	this->enemySpawners[5] = new SpawnPoint(910, -80, DIRECTION_UP, -100, 80, 3.2, 2);

	this->powerUpSpawnPoints = 4;

	if(powerUpSpawnPoints > 0)
		this->powerUpSpawners = new SpawnPoint*[powerUpSpawnPoints]();

	this->powerUpSpawners[0] = new SpawnPoint(512, 0, DIRECTION_DOWN, 0, 800, 25, 8);
	this->powerUpSpawners[1] = new SpawnPoint(512, 0, DIRECTION_DOWN, 0, 800, 9, 5);
	this->powerUpSpawners[2] = new SpawnPoint(512, 0, DIRECTION_DOWN, 0, 800, 50, 20);
	this->powerUpSpawners[3] = new SpawnPoint(512, 0, DIRECTION_DOWN, 0, 800, 28, 12);

	if(powerUpSpawnPoints > 0)
		this->powerUpSpawnerType = new PowerUpType[powerUpSpawnPoints]();

	this->powerUpSpawnerType[0] = POWERUP_HEALTH;
	this->powerUpSpawnerType[1] = POWERUP_POINTS;
	this->powerUpSpawnerType[2] = POWERUP_INVINCIBILITY;
	this->powerUpSpawnerType[3] = POWERUP_ROCKETS;

	this->powerUpHealthBonus = 10;
	this->powerUpNitroBonus = 0;
	this->powerUpPointsBonus = 2500;
	this->powerUpInvincibilityBonus = 5;
	this->powerUpRocketsBonus = 1;

	this->startRockets = 3;
	this->rocketSpeed = 400;
	this->rocketDamage = 25;

	this->survivalPoints = 200;
	this->rocketHitPoints = 500;
	this->carDestroyedPoints = 1000;
}

Level01::Level01(const Level& level) : Level(level)
{

}

Level01::~Level01()
{

}

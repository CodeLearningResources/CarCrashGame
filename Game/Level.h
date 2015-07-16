/*
 * Level.h
 *
 *  Created on: 6-apr.-2015
 *      Author: Thomas
 */

#ifndef GAME_LEVEL_H_
#define GAME_LEVEL_H_

#include <string>

#include "Spawnpoint.h"
#include "GameAssets.h"
#include "../GameElements/Car.h"
#include "../GameElements/PowerUp.h"

namespace CCG
{
	/*
	 * Template class for defining level classes
	 */
	class Level
	{
		public:
			Level(const Level& level);
			virtual ~Level(void);

			/*
			 * Get the index of the level
			 * @return level index
			 */
			int getLevelIndex(void) const;

			/*
			 * Get the name of the level
			 * @return level name
			 */
			std::string getName(void) const;

			/*
			 * Get the duration time for one level
			 * (Used in future gamemodes)
			 * @return round time
			 */
			float getRoundTime(void) const;

			/*
			 * Get the used background for the level
			 * @return background type
			 */
			BackgroundType getMap(void) const;

			/*
			 * Difficulty indicator of the level
			 * @return difficulty level of the level
			 */
			int getDifficulty(void) const;

			/*
			 * Move boundaries for the playercar
			 * @param x Top left X-position of the boundary box
			 * @param y Top left Y-position of the boundary box
			 * @param width Width of the boundary box
			 * @param height Height of the boundary box
			 */
			void getLevelBoundaries(int* x, int* y, int* width, int* height);

			/*
			 * Get the size of the background used
			 * @param x Width of the background
			 * @param y Height of the background
			 */
			void getBackgroundSize(float* x, float* y);

			/*
			 * Set the direction of the game (scroll direction of the background)
			 * @return game direction
			 */
			Direction getLevelDirection(void) const;

			/*
			 * Set the speed at the start of the game
			 * @return start game speed
			 */
			float getStartGameSpeed(void) const;

			/*
			 * Get the acceleration of the level per tick
			 * @return acceleration per tick
			 */
			float getAccelerationGameSpeed(void) const;

			/*
			 * Get the maximum acceleration of the level
			 * @return maximum acceleration of the level
			 */
			float getMaxAccelerationGameSpeed(void) const;

			/*
			 * Get the acceleration time of the enemy spawners
			 * @return acceleration time of the enemy spawners
			 */
			float getEnemySpawnAccelerationTime(void) const;

			/*
			 * Get the maximum acceleration time of the enemy spawners
			 * @return maximum acceleration time of the enemy spawners
			 */
			float getEnemySpawnMaxAccelerationTime(void) const;

			/*
			 * Get the maximum enemy entities allowed at a time on screen
			 * @return maximum enemy entities at a time
			 */
			int getEnemyMaxEntities(void) const;

			/*
			 * Get the points given to player per second they are alive
			 * @return survival bonus points
			 */
			int getSurvivalPointsPerSecond(void) const;

			/*
			 * Get the amount of damage for rockets
			 * @return damage points for rockets
			 */
			int getRocketHitPoints(void) const;

			/*
			 * Get the points for destroying an enemy car
			 * @return points rewarded for destroying enemy
			 */
			int getCarDestroyedPoints(void) const;

			/*
			 * Get the size of the spawn area for enemy spawners
			 * @return spawn size for enemy spawners
			 */
			int getEnemySpawnPointsSize(void) const;

			/*
			 * Get the size of the spawn area for power-up spawners
			 * @return spawn size for power-up spawners
			 */
			int getPowerUpSpawnPointsSize(void) const;

			/*
			 * Get the value for each type of bonus
			 * @param bonus Type of bonus
			 * @return The value for that bonus
			 */
			int getPowerUpBonusValue(PowerUpBonus bonus) const;

			/*
			 * Get type of bonus for each power-up spawner
			 * @return array of power-up for each power-up spawner
			 */
			PowerUpType* getPowerUpSpawnPointsTypes(void) const;

			/*
			 * Get the spawn point of the player at the start of the level intro
			 * @return spawn point for spawning the player
			 */
			SpawnPoint* getPlayerSpawnPoint(void) const;

			/*
			 * Get the start point for the player at the end of the level intro
			 * @param x The X-position of the player car
			 * @param y The Y-position of the player car
			 */
			void getPlayerStartPoint(float* x, float* y);

			/*
			 * Get all defined enemy spawners
			 * @return list of enemy spanwers
			 */
			SpawnPoint** getEnemySpawnPoints(void) const;

			/*
			 * Get all defined power-up spawners
			 * @return list of power-up spawners
			 */
			SpawnPoint** getPowerUpSpawnPoints(void) const;

			/*
			 * Get start amount of rockets for each player
			 * @return amount of rockets to start with
			 */
			int getStartRockets(void) const;

			/*
			 * Get the travel speed of the rockets
			 * @return travel speeld of rocket
			 */
			float getRocketSpeed(void) const;

			/*
			 * Get the damage that rockets deal
			 * @return rocket damage
			 */
			int getRocketDamage(void) const;


		protected:
			Level(void);

			//Level info
			int levelIndex;
			std::string levelName;
			float roundTime;
			BackgroundType mapType;
			int difficulty;

			//Game info
			//-Level boundaries for player
			int boundaryX;
			int boundaryY;
			int boundaryWidth;
			int boundaryHeight;
			Direction levelDirection;

			//-Background size
			float backgroundSizeX;
			float backgroundSizeY;

			//-Gamespeed
			float startGameSpeed;
			float accelerationGameSpeed;
			float maxAccelerationGameSpeed;

			//-Spawn enemy cars
			int enemyMaxEntities;
			float enemySpawnAccelerationTime;
			float enemySpawnMaxAccelerationTime;

			//-Spawnpoints
			//--Player spawn point
			SpawnPoint* playerSpawnPoint;
			float startLocationX, startLocationY;

			//--Enemy spawnpoints
			int enemySpawnPoints;
			SpawnPoint** enemySpawners;

			//--Power up spawnpoints
			int powerUpSpawnPoints;
			PowerUpType* powerUpSpawnerType;
			SpawnPoint** powerUpSpawners;

			//-Power up
			int powerUpHealthBonus;
			int powerUpNitroBonus;
			int powerUpPointsBonus;
			int powerUpInvincibilityBonus;
			int powerUpRocketsBonus;

			//-Rocket
			int startRockets;
			float rocketSpeed;
			int rocketDamage;

			//-Score
			int survivalPoints;
			int rocketHitPoints;
			int carDestroyedPoints;
	};
}

#endif /* GAME_LEVEL_H_ */

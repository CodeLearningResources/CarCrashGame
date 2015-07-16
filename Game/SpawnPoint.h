/*
 * SpawnPoint.h
 *
 *  Created on: 14-apr.-2015
 *      Author: Thomas
 */

#ifndef GAME_SPAWNPOINT_H_
#define GAME_SPAWNPOINT_H_

#include <stdlib.h>
#include <time.h>
#include <list>

#include "Timer.h"
#include "../GameElements/GameElement.h"

namespace CCG
{
	/*
	 * Spawn area for objects to be placed randomly at a random time interval
	 */
	class SpawnPoint
	{
		public:
			/*
			 * Default constructor
			 */
			SpawnPoint(void);

			/*
			 * Constructor
			 * @param posX X-position of spawner
			 * @param posY Y-position of spawner
			 * @param spawnDirection Orientation of the objects when spawned
			 * @param moveSpeed Default velocity for the objects when spawned
			 * @param spawnBoxSize The size where the objects can spawn
			 * @param spawnDelay Default delay between each spawn
			 * @param spawnDelayOffset Adds a random offset in the interval [default-offset; default+offset]
			 */
			SpawnPoint(int posX, int posY, Direction spawnDirection, float moveSpeed, int spawnBoxSize, float spawnDelay, float spawnDelayOffset);

			/*
			 * Copy constructor
			 */
			SpawnPoint(const SpawnPoint& spawnPoint);

			/*
			 * Destructor
			 */
			virtual ~SpawnPoint(void);

			/*
			 * Initialization of the spawner
			 * @param spawnTimer Timer object for driving the spawn process
			 */
			void initialize(Timer* spawnTimer);

			/*
			 * Set the time to shorten the spawn delay
			 * @param accelerationTime Time to shorten the spawn delay
			 */
			void setSpawnDelayAcceleration(float accelerationTime);

			/*
			 * Get the direction of the spawner
			 * @return Direction to spawn the objects
			 */
			Direction getSpawnDirection(void);

			/*
			 * Get the movement speed for the spawned objects
			 * @return Speed for the spawned objects
			 */
			float getMoveSpeed(void);

			/*
			 * Add a object to the spawn queue
			 */
			void queueObject(GameElement* object);

			/*
			 * Force to spawn the next object in the spawn queue
			 */
			void spawnObject(GameElement* object);

			/*
			 * Clear all object in the spawn queue
			 */
			void clearQueue(void);

			/*
			 * Start the spawn timer
			 */
			void start(void);

			/*
			 * Pause the spawn timer
			 */
			void pause(void);

			/*
			 * Check for a new spawn
			 */
			void update(void);

			/*
			 * Cancel the next object from spawning
			 */
			void cancelNextSpawn(void);

			/*
			 * Check if the spawner is empty
			 * @return The state if the spawner is empty
			 */
			bool isEmpty(void);

			/*
			 * Get the top most object in the spawner
			 */
			GameElement* getNextObject(void);

		private:
			int posX, posY;
			Direction spawnDirection;
			float moveSpeed;
			int spawnBoxSize;
			float spawnDelay;
			float spawnDelayOffset;
			float spawnDelayAcceleration;
			float nextSpawn;
			std::list<GameElement*>* objectQueue;
			Timer* spawnTimer;
	};
}

#endif /* GAME_SPAWNPOINT_H_ */

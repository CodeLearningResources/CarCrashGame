/*
 * Car.h
 *
 *  Created on: 9-mrt.-2015
 *      Author: Thomas
 */

#ifndef GAMEELEMENTS_CAR_H_
#define GAMEELEMENTS_CAR_H_

#include "GameElement.h"

namespace CCG
{
	//Constants
	#define CAR_TURN_ROTATION_MAX 20		//Rotation of the car when moving sideways

	/*
	 * Abstract game element class for cars
	 */
	class Car : public GameElement
	{
		public:
			~Car(void);

			Direction getDriveDirection(void) const;
			int getHealth(void) const;
			int getNitro(void) const;
			float getInvincibleTime(void) const;

			bool isInvincible(void) const;
			bool isAlive(void) const;

			void setDriveDirection(Direction direction);
			void setHealth(int points);
			void setNitro(int points);
			void setInvincibleTime(float time);

			void setAlive(bool flag);

			void heal(int points);
			void hit(int points);

			//Moving the car
			void goLeft(bool flag);
			void goRight(bool flag);
			void goUp(bool flag);
			void goDown(bool flag);
			void stopMovement(void);

			/*
			 * Automatically move the car to the given location
			 * @param x The X-position of the location
			 * @param y The Y-position of the location
			 * @param flag Let the car move to the set location
			 */
			void moveToLocation(float x, float y, bool flag);

			void useNitro(bool flag);

			/*
			 * Check if the car is in the level boundaries and correct the movement if needed
			 */
			void keepInLevelBoundaries(int x, int y, int width, int height);

			void move(float timeStep);	//Override of move method
			void updateStatus(float timeStep);

			virtual void playCrashSound(void) = 0;
			virtual void playNitroSound(void) = 0;
			virtual void stopNitroSound(void) = 0;

		private:
			int health;
			int nitro;
			float invincibleTime;

			float moveToX, moveToY;
			bool moveToFlag;

			bool alive;

			Direction direction;

			bool left;
			bool right;
			bool up;
			bool down;

		protected:
			Car(void);
			Car(int health, int nitro);
			Car(const Car& car);
	};
}

#endif /* GAMEELEMENTS_CAR_H_ */

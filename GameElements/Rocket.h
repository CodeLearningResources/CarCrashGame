/*
 * Rocket.h
 *
 *  Created on: 8-jun.-2015
 *      Author: Thomas
 */

#ifndef GAMEELEMENTS_ROCKET_H_
#define GAMEELEMENTS_ROCKET_H_

#include "GameElement.h"
#include "../Game/Player.h"

namespace CCG
{
	/*
	 * Abstract game element class for rockets
	 */
	class Rocket : public GameElement
	{
		public:
			~Rocket(void);

			int getHitPoints(void);
			float getSpeed(void);
			Direction getDirection(void);
			Player* getOwner(void);

			bool isAlive(void);

			void setHitPoints(int hitPoints);
			void setSpeed(float speed);
			void setDirection(Direction direction);
			void setAlive(bool flag);
			void setOwner(Player* owner);

			virtual void playLaunchSound(void) = 0;

		private:
			int hitPoints;
			float speed;
			Direction direction;
			bool alive;
			Player* owner;

		protected:
			Rocket(void);
			Rocket(int hitPoints, float speed, Direction direction, Player* owner);
			Rocket(const Rocket& rocket);
	};
}

#endif /* GAMEELEMENTS_ROCKET_H_ */

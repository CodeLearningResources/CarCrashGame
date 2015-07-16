/*
 * PowerUp.h
 *
 *  Created on: 19-apr.-2015
 *      Author: Thomas
 */

#ifndef GAMEELEMENTS_POWERUP_H_
#define GAMEELEMENTS_POWERUP_H_

#include "GameElement.h"

namespace CCG
{
	enum PowerUpBonus
	{
		POWERUP_BONUS_HEALTH,
		POWERUP_BONUS_NITRO,
		POWERUP_BONUS_POINTS,
		POWERUP_BONUS_ROCKETS,
		POWERUP_BONUS_INVINCIBILITY
	};

	/*
	 * Abstract game element class for power-ups
	 */
	class PowerUp : public GameElement
	{
		public:
			~PowerUp(void);

			PowerUpBonus getBonusType(void);
			int getBonusValue(void);

			bool isAvailable(void);

			void setBonusValue(int bonusValue);
			void setAvailability(bool flag);

		private:
			PowerUpBonus bonus;
			int bonusValue;
			bool available;

		protected:
			PowerUp(void);
			PowerUp(PowerUpBonus bonus);
			PowerUp(const PowerUp& powerUp);
	};
}

#endif /* GAMEELEMENTS_POWERUP_H_ */

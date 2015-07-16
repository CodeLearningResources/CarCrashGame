/*
 * HUD.h
 *
 *  Created on: 30-mrt.-2015
 *      Author: Thomas
 */

#ifndef GAMEELEMENTS_HUD_H_
#define GAMEELEMENTS_HUD_H_

#define MAX_PLAYERS 4

#include <stdio.h>

#include "GameElement.h"
#include "../Game/Player.h"

namespace CCG
{
	/*
	 * Abstract game element class for HUD's
	 */
	class HUD : public GameElement
	{
		public:
			~HUD(void);

			void setPlayer(Player* player, int playerNumber);		//Assign player to HUD (up to MAX_PLAYERS)
			void setThisPlayer(int playerNumber);					//Connect the advanced HUD for this player

			Player* getPlayer(int playerNumber) const;
			int getThisPlayer(void) const;

		private:
			Player** players;
			int numberOfPlayers;
			int thisPlayer;

		protected:
			HUD(void);
	};
}

#endif /* GAMEELEMENTS_HUD_H_ */

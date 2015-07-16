/*
 * GameManager.h
 *
 *  Created on: 5-apr.-2015
 *      Author: Thomas
 */

#ifndef GAME_GAMEMANAGER_H_
#define GAME_GAMEMANAGER_H_

#include "Player.h"
#include "GameHighscore.h"
#include "../Levels/Levels.h"

namespace CCG
{
	/*
	 * Hold all global used objects in the game
	 */
	class GameManager
	{
		public:
			GameManager(void);
			virtual ~GameManager(void);

			/*
			 * Set the current player
			 * @param player This player
			 */
			void setThisPlayer(Player* player);

			/*
			 * Get the current player
			 * @return This player
			 */
			Player* getThisPlayer(void);

			/*
			 * Get the level configuration
			 * @param Level index
			 * @return The level configuration object, NULL if given index is out of range
			 */
			Level* getLevel(int level);

			/*
			 * Get the number of available levels
			 * @return Number of available levels
			 */
			int availableLevels(void);

			//////////////////////////////////////////
			// Following methods in development
			//////////////////////////////////////////
			/*
			 * Add possible highscore to the list
			 * @param level The index of the level
			 * @param playerName The name of the player for the entry
			 * @param score The score of the player for the entry
			 * @return True if a new highscore was added, False if is not a highscore
			 */
			bool addHighscore(int level, std::string playerName, int score);
			///////////////////////////////////////////
			//  End in development
			///////////////////////////////////////////

		private:
			Player* currentPlayer;
			Levels* levelManager;
			//GameHighscore* highscores;
	};
}

#endif /* GAME_GAMEMANAGER_H_ */

/*
 * GameHighscore.h
 *
 *  Created on: 20-jun.-2015
 *      Author: Thomas
 */

#ifndef GAME_GAMEHIGHSCORE_H_
#define GAME_GAMEHIGHSCORE_H_

#include <list>
#include <vector>

#include "HighscoreEntry.h"

namespace CCG
{
	#define NUMBER_OF_TOPSCORES 5

	/*
	 * Class to keep all highscores of each level
	 * CLASS IN DEVELOPMENT
	 */
	class GameHighscore
	{
		public:
			/*
			 * Constructor
			 * @param Number of levels to keep highscores from
			 */
			GameHighscore(int maxLevels);
			~GameHighscore(void);

			//////////////////////////////////////////
			// Following methods in development
			//////////////////////////////////////////
			/*
			 * Clear all highscores
			 */
			void resetHighscores(void);

			int loadHighscores(const char* fileLocation);
			int saveHighscores(const char* fileLocation);

			/*
			 * Add possible highscore to the list
			 * @param level The index of the level
			 * @param playerName The name of the player for the entry
			 * @param score The score of the player for the entry
			 * @return True if a new highscore was added, False if is not a highscore
			 */
			bool addHighscore(int level, std::string playerName, int score);

			/*
			 * Get the list of all highscores from a level
			 * @param level The index of the level
			 * @return The list of the selected level
			 */
			std::list<HighscoreEntry*>* getHighscores(int level);

			/*
			 * Get the maximum length of entries in a highscore list
			 * @return The maximum number of entries in a list
			 */
			int getNumberOfTopscores(void);

			//////////////////////////////////////////
			// End in development
			//////////////////////////////////////////

		private:
			int maxLevels;
			std::vector< std::list<HighscoreEntry*>* >* highscoreList;

		protected:
			GameHighscore(void);
	};
}

#endif /* GAME_GAMEHIGHSCORE_H_ */

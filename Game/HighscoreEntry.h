/*
 * HighscoreEntry.h
 *
 *  Created on: 21-jun.-2015
 *      Author: Thomas
 */

#ifndef GAME_HIGHSCOREENTRY_H_
#define GAME_HIGHSCOREENTRY_H_

#include <string>

namespace CCG
{
	/*
	 * Class to define highscore entries
	 */
	class HighscoreEntry
	{
		public:
			/*
			 * Default constructor
			 */
			HighscoreEntry(void);

			/*
			 * Constructor
			 * @param name Name of the player
			 * @param score Score that the player achieved
			 */
			HighscoreEntry(std::string name, int score);

			/*
			 * Copy constructor
			 */
			HighscoreEntry(const HighscoreEntry& entry);

			/*
			 * Destructor
			 */
			virtual ~HighscoreEntry(void);

			/*
			 * Set the name of the player
			 * @param name Name of the player
			 */
			void setName(std::string name);

			/*
			 * Set the score of the entry
			 * @param score Score that the player achieved
			 */
			void setScore(int score);

			/*
			 * Get the name of player
			 * @return Name of the player
			 */
			std::string getName(void);

			/*
			 * Get the score of the entry
			 * @return Score that the player achieved
			 */
			int getScore(void);

		private:
			std::string name;
			int score;
	};
}

#endif /* GAME_HIGHSCOREENTRY_H_ */

/*
 * Game.h
 *
 *  Created on: 9-mrt.-2015
 *      Author: Thomas
 */

#ifndef GAME_GAME_H_
#define GAME_GAME_H_

#include <stdio.h>
#include "KeyboardKey.h"
#include "GameFactory.h"
#include "GameStateManager.h"
#include "GameSplash.h"
#include "GameLevel.h"
#include "GameManager.h"
#include "GameConfigManager.h"
#include "../Levels/Levels.h"

namespace CCG
{
	/*
	 * Main game class which initializes the game and contains the game loop
	 */
	class Game
	{
		public:
			/*
			 * Default constructor
			 */
			Game(void);

			/*
			 * Constructor
			 * @param factory The game factory which returns game objects
			 */
			Game(GameFactory* factory);

			/*
			 * Constructor
			 * @param factory The game factory which returns game objects
			 * @param debug Toggle debugmode to print more information to terminal
			 */
			Game(GameFactory* factory, bool debug);

			/*
			 * Copy constructor
			 */
			Game(const Game& game);

			/*
			 * Destructor
			 */
			virtual ~Game(void);

			/*
			 * Start the game
			 * @return Exit state of the game, '0' if no error occurred
			 */
			int launch(void);

			/*
			 * Load a configuration XML file to adjust the current settings
			 * @param configLocation The file location of the configuration file
			 */
			void loadConfigurations(const char* configLocation);

			/*
			 * Save a configuration XML file of the current settings
			 * @param configLocation The file location for the configuration file
			 */
			void saveConfigurations(const char* configLocation);

		private:
			GameFactory* factory;				//Game factory
			GameStateManager* stateManager;		//State manager to hold the current game state
			GameManager* gameManager;			//Game manager
			GameConfigManager* configManager;	//Configuration manager to load/save configuration
			bool debug;							//Debug mode activated/deactivated
	};
}

#endif /* GAME_GAME_H_ */

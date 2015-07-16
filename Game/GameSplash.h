/*
 * GameSplash.h
 *
 *  Created on: 12-apr.-2015
 *      Author: Thomas
 */

#ifndef GAME_GAMESPLASH_H_
#define GAME_GAMESPLASH_H_

#include <stdlib.h>

#include "GameState.h"
#include "Event.h"
#include "GameFactory.h"
#include "GameStartMenu.h"
#include "GameManager.h"

namespace CCG
{
	/*
	 * Game state while initializing the game assets
	 */
	class GameSplash : public GameState
	{
		public:
			/*
			 * Constructor
			 * @see GameState
			 */
			GameSplash(GameFactory* factory, GameStateManager* stateManager, GameManager* gameManager);
			~GameSplash(void);

			/*
			 * Initialize the state
			 * @see GameState
			 */
			void initialize(void);

			/*
			 * Release the state
			 * @see GameState
			 */
			void release(void);

			/*
			 * Pause the state
			 * @see GameState
			 */
			void pause(void);

			/*
			 * Resume the state
			 * @see GameState
			 */
			void resume(void);

			/*
			 * Handle the given event
			 * @see GameState
			 */
			void handleEvents(Event* event);

			/*
			 * Call all update functions of all elements to be displayed in the window
			 * @see GameState
			 */
			void update(void);

		private:
			bool skip;						//Skip the splash art before the fadeoutTimer is finished and after all asset is loaded
			Timer* frameTimer = NULL;
			Timer* fadeoutTimer = NULL;
			Picture* splashArt = NULL;

		protected:
			GameSplash(void);
	};
}

#endif /* GAME_GAMESPLASH_H_ */

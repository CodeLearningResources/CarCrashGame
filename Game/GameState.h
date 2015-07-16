/*
 * GameState.h
 *
 *  Created on: 31-mrt.-2015
 *      Author: Thomas
 */

#ifndef GAME_GAMESTATE_H_
#define GAME_GAMESTATE_H_

#include <stdio.h>

#include "GameFactory.h"
#include "GameStateManager.h"
#include "GameManager.h"
#include "Event.h"

namespace CCG
{
	/*
	 * Abstract class for a state of the game
	 */
	class GameState
	{
		public:
			virtual ~GameState(void);

			/*
			 * Initialize the state
			 */
			virtual void initialize(void) = 0;

			/*
			 * Release the state
			 */
			virtual void release(void) = 0;

			/*
			 * Pause the state
			 */
			virtual void pause(void) = 0;

			/*
			 * Resume the state
			 */
			virtual void resume(void) = 0;

			/*
			 * Handle the given event
			 * @param event Event to be handled by the state
			 */
			virtual void handleEvents(Event* event) = 0;

			/*
			 * Call all update functions of all elements to be displayed in the window
			 */
			virtual void update(void) = 0;

		protected:
			GameState(void);
			GameState(GameFactory* factory, GameStateManager* stateManager, GameManager* gameManager);

			GameFactory* factory;
			GameStateManager* stateManager;
			GameManager* gameManager;
	};
}

#endif /* GAME_GAMESTATE_H_ */

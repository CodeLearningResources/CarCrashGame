/*
 * GameStateManager.h
 *
 *  Created on: 29-mrt.-2015
 *      Author: Thomas
 */

#ifndef GAME_GAMESTATEMANAGER_H_
#define GAME_GAMESTATEMANAGER_H_

#include <stdio.h>
#include <vector>

#include "Event.h"

namespace CCG
{
	class GameState;	//Declare for compiler

	/*
	 * State machine to hold all game states
	 */
	class GameStateManager
	{
		public:
			/*
			 * Default constructor
			 */
			GameStateManager(void);

			/*
			 * Destructor
			 */
			virtual ~GameStateManager(void);

			/*
			 * Release all states on the stack
			 */
			void releaseStack(void);

			/*
			 * Remove all states on the stack and place the given new one
			 * @param state New game state
			 */
			void setState(GameState* state);

			/*
			 * Pause the current state and place the given state above to be runned
			 * @param state New game state
			 */
			void pushState(GameState* state);

			/*
			 * Remove the top most state from the stack
			 */
			void popState(void);

			/*
			 * Stop the game loop and execute the game close procedure
			 */
			void exitGame(void);

			/*
			 * Get the top most state from the stack
			 * @return The top most state
			 */
			GameState* getState(void);

			/*
			 * Get the running state
			 * @return Indicator if the game has called to terminate the program
			 */
			bool getRunningState(void);

			/*
			 * Give the event to the top most state to handle the event
			 * @param event Event to be handled by the current running state
			 */
			void handleEvents(Event* event);

			/*
			 * Call the update function of the current running state
			 */
			void update(void);

		private:
			std::vector<GameState*>* states;
			bool running;
	};
}

#endif /* GAME_GAMESTATEMANAGER_H_ */

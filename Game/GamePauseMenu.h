/*
 * GamePauseMenu.h
 *
 *  Created on: 24-apr.-2015
 *      Author: Thomas
 */

#ifndef GAME_GAMEPAUSEMENU_H_
#define GAME_GAMEPAUSEMENU_H_

#include <stdlib.h>

#include "GameManager.h"
#include "MusicPlayer.h"
#include "GameState.h"
#include "Event.h"
#include "GameStartMenu.h"
#include "GameOptionsMenu.h"

namespace CCG
{
	/*
	 * State displayed when main game is paused
	 */
	class GamePauseMenu : public GameState
	{
		public:
			/*
			 * Constructor
			 * @see GameState
			 */
			GamePauseMenu(GameFactory* factory, GameStateManager* stateManager, GameManager* gameManager);
			~GamePauseMenu(void);

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
			 * Call all update functions of all elements (buttons,...) to be displayed in the window
			 * @see GameState
			 */
			void update(void);

			/*
			 * Handle the events of all displayed buttons
			 * @param mouseX The X-position of the cursor
			 * @param mouseY The Y-position of the cursor
			 * @param mousePressed The state of the mouse button
			 */
			void handleButtonsEvents(int mouseX, int mouseY, bool mousePressed);

		private:
			Timer* frameTimer = NULL;
			Background* background = NULL;
			Button* resumeButton = NULL;
			Button* optionButton = NULL;
			Button* exitButton = NULL;
			Text* pauseText = NULL;
			Text* resumeText = NULL;
			Text* optionText = NULL;
			Text* exitText = NULL;

		protected:
			GamePauseMenu(void);
	};
}

#endif /* GAME_GAMEPAUSEMENU_H_ */

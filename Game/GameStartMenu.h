/*
 * GameStartMenu.h
 *
 *  Created on: 12-apr.-2015
 *      Author: Thomas
 */

#ifndef GAME_GAMESTARTMENU_H_
#define GAME_GAMESTARTMENU_H_

#include <stdlib.h>

#include "GameManager.h"
#include "MusicPlayer.h"
#include "GameState.h"
#include "Event.h"
#include "GameSinglePlayerMenu.h"
#include "GameOptionsMenu.h"

namespace CCG
{
	/*
	 * Main start screen
	 */
	class GameStartMenu : public GameState
	{
		public:
			/*
			 * Constructor
			 * @see GameState
			 */
			GameStartMenu(GameFactory* factory, GameStateManager* stateManager, GameManager* gameManager);
			~GameStartMenu(void);

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
			MusicPlayer* musicPlayer = NULL;
			Timer* frameTimer = NULL;
			Background* background = NULL;
			Picture* gameLogo = NULL;
			Button* singlePlayerButton = NULL;
			Button* multiPlayerButton = NULL;
			Button* optionButton = NULL;
			Button* exitButton = NULL;
			Messagebox* messagebox = NULL;
			Text* singlePlayerText = NULL;
			Text* multiPlayerText = NULL;
			Text* optionText = NULL;
			Text* exitText = NULL;

		protected:
			GameStartMenu(void);
	};
}

#endif /* GAME_GAMESTARTMENU_H_ */

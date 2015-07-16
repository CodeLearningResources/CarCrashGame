/*
 * GameSinglePlayerMenu.h
 *
 *  Created on: 16-apr.-2015
 *      Author: Thomas
 */

#ifndef GAME_GAMESINGLEPLAYERMENU_H_
#define GAME_GAMESINGLEPLAYERMENU_H_

#include <stdlib.h>

#include "MusicPlayer.h"
#include "GameState.h"
#include "Event.h"
#include "Level.h"
#include "GameLevel.h"

namespace CCG
{
	/*
	 * Game state to select and start a single player game
	 */
	class GameSinglePlayerMenu : public GameState
	{
		public:
			/*
			 * Constructor
			 * @see GameState
			 */
			GameSinglePlayerMenu(GameFactory* factory, GameStateManager* stateManager, GameManager* gameManager, Background* background);
			~GameSinglePlayerMenu(void);

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

			/*
			 * Select next level in levelselect
			 */
			void nextLevel(void);

			/*
			 * Select previous level in levelselect
			 */
			void previousLevel(void);

			/*
			 * Select next car in carselect
			 */
			void nextCar(void);

			/*
			 * Select previous car in carselect
			 */
			void previousCar(void);

			/*
			 * Update the selected level display
			 */
			void updateLevelPreview(int selectedLevel);

			/*
			 * Update the selected car display
			 */
			void updateCarPreview(int selectedCar);

			/*
			 * Update the name textbox
			 * @param event Keyboard event to modify the text in the name textbox
			 */
			void updateNameTextbox(Event* event);

			/*
			 * Initialize the player with the new name and car
			 */
			void setPlayer(void);

		private:
			MusicPlayer* musicPlayer = NULL;
			Timer* frameTimer = NULL;
			Background* background = NULL;
			Picture* carPicture = NULL;
			Textbox* playernameTextbox = NULL;
			Button* returnButton = NULL;
			Button* startButton = NULL;
			Button* nextLevelButton = NULL;
			Button* prevLevelButton = NULL;
			Button* nextCarButton = NULL;
			Button* prevCarButton = NULL;
			Text* singlePlayerText = NULL;
			Text* menuPlayernameText = NULL;
			Text* menuLevelText = NULL;
			Text* menuCarText = NULL;
			Text* returnText = NULL;
			Text* startText = NULL;
			Text* nextLevelText = NULL;
			Text* prevLevelText = NULL;
			Text* nextCarText = NULL;
			Text* prevCarText = NULL;
			Text* currentLevelText = NULL;

			int selectedCar;
			int selectedLevel;
			std::string playerName;

		protected:
			GameSinglePlayerMenu(void);
	};
}

#endif /* GAME_GAMESINGLEPLAYERMENU_H_ */

/*
 * GameControlsMenu.h
 *
 *  Created on: 10-jun.-2015
 *      Author: Thomas
 */

#ifndef GAME_GAMECONTROLSMENU_H_
#define GAME_GAMECONTROLSMENU_H_

#include <string.h>

#include "GameFactory.h"
#include "GameStateManager.h"
#include "GameManager.h"
#include "Player.h"
#include "GameState.h"
#include "Event.h"

namespace CCG
{
	/*
	 * Game state to customize the player controls
	 */
	class GameControlsMenu : public GameState
	{
		public:
			/*
			 * Constructor
			 * @see GameState
			 */
			GameControlsMenu(GameFactory* factory, GameStateManager* stateManager, GameManager* gameManager, Background* background);
			~GameControlsMenu(void);

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
			 * Update the values of all elements (buttons,...) on the screen
			 */
			void updateValues(void);

			/*
			 * Call all update functions of all elements (buttons,...) to be displayed in the window
			 * @see GameState
			 */
			void update(void);

			/*
			 * Assign a new key to the selected control
			 * @param key New keyboard key
			 * @param selectedControl The selected control which to bind the keyboard key
			 * @return 0 if succeeded, -1 if selectedControl is out of range, -2 if key is not defined
			 */
			int assignKeyToControl(KeyboardKey* key, int selectedControl);

			/*
			 * Reload the settings from the gameManager
			 */
			void restoreSettings(void);

			/*
			 * Apply the made changes to the gameManager
			 */
			bool applySettings(void);

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
			Messagebox* messagebox = NULL;
			Button** controlsButtons = NULL;
			Button* restoreButton = NULL;
			Button* applyButton = NULL;
			Button* cancelButton = NULL;
			Text* optionsText = NULL;
			Text** controlsTexts = NULL;
			Text** controlsValueTexts = NULL;
			Text* restoreText = NULL;
			Text* applyText = NULL;
			Text* cancelText = NULL;

			KeyboardKey** controlMapping = NULL;	//Current modified controls
			int getKeyForControl;					//Indicator which control will be modified, -1 if none

		protected:
			GameControlsMenu(void);
	};
}

#endif /* GAME_GAMECONTROLSMENU_H_ */

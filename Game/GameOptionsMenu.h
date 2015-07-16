/*
 * GameOptionsMenu.h
 *
 *  Created on: 17-apr.-2015
 *      Author: Thomas
 */

#ifndef GAME_GAMEOPTIONSMENU_H_
#define GAME_GAMEOPTIONSMENU_H_

#include "GameFactory.h"
#include "GameStateManager.h"
#include "GameManager.h"
#include "GameState.h"
#include "Event.h"
#include "GameControlsMenu.h"

namespace CCG
{
	/*
	 * Game state to customize the game settings
	 */
	class GameOptionsMenu : public GameState
	{
		public:
			/*
			 * Constructor
			 * @see GameState
			 */
			GameOptionsMenu(GameFactory* factory, GameStateManager* stateManager, GameManager* gameManager, Background* background);
			~GameOptionsMenu(void);

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
			 * Update the values of all elements (sliders,...) on the screen
			 */
			void updateValues(void);

			/*
			 * Call all update functions of all elements (buttons,...) to be displayed in the window
			 * @see GameState
			 */
			void update(void);

			/*
			 * Reload the settings
			 */
			void restoreSettings(void);

			/*
			 * Handle the events of all displayed buttons
			 * @param mouseX The X-position of the cursor
			 * @param mouseY The Y-position of the cursor
			 * @param mousePressed The state of the mouse button
			 */
			void handleButtonsEvents(int mouseX, int mouseY, bool mousePressed);

			/*
			 * Handle the events of all displayed sliders
			 * @param mouseX The X-position of the cursor
			 * @param mouseY The Y-position of the cursor
			 * @param mousePressed The state of the mouse button
			 */
			void handleSliderEvents(int mouseX, int mouseY, bool mousePressed);

			/*
			 * Handle the events of all displayed checkboxs
			 * @param mouseX The X-position of the cursor
			 * @param mouseY The Y-position of the cursor
			 * @param mousePressed The state of the mouse button
			 */
			void handleCheckboxEvents(int mouseX, int mouseY, bool mousePressed);

		private:
			Window* gameWindow = NULL;
			Timer* frameTimer = NULL;
			Background* background = NULL;
			MusicPlayer* musicPlayer = NULL;
			Button* controlsButton = NULL;
			Button* applyButton = NULL;
			Button* cancelButton = NULL;
			Slider* musicVolumeSlider = NULL;
			Slider* sfxVolumeSlider = NULL;
			Checkbox* vSyncCheckbox = NULL;
			Checkbox* fpsCapCheckbox = NULL;
			Text* optionsText = NULL;
			Text* musicText = NULL;
			Text* sfxText = NULL;
			Text* musicValueText = NULL;
			Text* sfxValueText = NULL;
			Text* vSyncText = NULL;
			Text* fpsCapText = NULL;
			Text* controlsText = NULL;
			Text* applyText = NULL;
			Text* cancelText = NULL;

			//Previous setting state
			int prevMusicVolume;
			int prevSFXVolume;
			int prevFPSCap;
			bool prevVSyncActive;

		protected:
			GameOptionsMenu(void);
	};
}

#endif /* GAME_GAMEOPTIONSMENU_H_ */

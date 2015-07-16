/*
 * GameFactory.h
 *
 *  Created on: 9-mrt.-2015
 *      Author: Thomas
 */

#ifndef GAME_GAMEFACTORY_H_
#define GAME_GAMEFACTORY_H_

#include "Event.h"
#include "Timer.h"
#include "Window.h"
#include "EventStack.h"
#include "GameAssets.h"

#include "MusicPlayer.h"
#include "Music.h"
#include "../GameElements/Car.h"
#include "../GameElements/PowerUp.h"
#include "../GameElements/Background.h"
#include "../GameElements/HUD.h"
#include "../GameElements/Text.h"
#include "../GameElements/Button.h"
#include "../GameElements/Textbox.h"
#include "../GameElements/Slider.h"
#include "../GameElements/Checkbox.h"
#include "../GameElements/Messagebox.h"
#include "../GameElements/Picture.h"
#include "../GameElements/Animation.h"
#include "../GameElements/Rocket.h"
#include "../GameElements/Cursor.h"

namespace CCG
{
	/*
	 * Abstract game factory
	 */
	class GameFactory
	{
		public:
			virtual ~GameFactory(void);

			/*
			 * Initialize factory before use
			 */
			virtual int initializeFactory(void) = 0;

			/*
			 * Release factory and all of it's objects
			 */
			virtual int releaseFactory(void) = 0;

			/*
			 * Load the game assets after initialization
			 */
			virtual int loadAsset(void) = 0;

			//Get function for all available objects
			virtual Window* getWindow(void) = 0;
			virtual EventStack* getEventStack(void) = 0;

			virtual Timer* getTimer(void) = 0;
			virtual Text* getText(std::string text, TextFont type) = 0;
			virtual Cursor* getCursor(void) = 0;

			virtual Car* getCar(CarType type) = 0;
			virtual PowerUp* getPowerUp(PowerUpType type) = 0;
			virtual Background* getBackground(BackgroundType type) = 0;
			virtual HUD* getHUD(HUDType type) = 0;
			virtual Button* getButton(ButtonType type) = 0;
			virtual Textbox* getTextbox(TextboxType type) = 0;
			virtual Slider* getSlider(SliderType type) = 0;
			virtual Checkbox* getCheckbox(CheckboxType type) = 0;
			virtual Messagebox* getMessagebox(MessageboxType type) = 0;
			virtual Picture* getPicture(PictureType type) = 0;
			virtual Animation* getAnimation(AnimationType type) = 0;
			virtual Rocket* getRocket(RocketType type) = 0;

			virtual MusicPlayer* getMusicPlayer(void) = 0;
			virtual Music* getMusic(MusicType type) = 0;

			/*
			 * Get the screen width in pixels
			 * @return Screen width in pixels
			 */
			int getScreenWidth(void);

			/*
			 * Get the screen height in pixels
			 * @return Screen height in pixels
			 */
			int getScreenHeight(void);

		private:
			int SCREEN_WIDTH;
			int SCREEN_HEIGHT;

		protected:
			GameFactory(void);
			GameFactory(int width, int height);
	};
}

#endif /* GAME_GAMEFACTORY_H_ */

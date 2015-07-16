/*
 * SDLFactory.h
 *
 *  Created on: 9-mrt.-2015
 *      Author: Thomas
 */

#ifndef SDLENGINE_SDLFACTORY_H_
#define SDLENGINE_SDLFACTORY_H_

#include <stdio.h>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

#include "../Game/GameFactory.h"
#include "../Game/Timer.h"
#include "../Game/GameAssets.h"
#include "../Game/MusicPlayer.h"
#include "../Game/Music.h"
#include "../GameElements/GameElement.h"
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
#include "SDLAssetLib.h"
#include "SDLEventStack.h"
#include "SDLTimer.h"
#include "SDLKeyboardEvent.h"
#include "SDLTexture.h"
#include "SDLWindow.h"
#include "SDLCar.h"
#include "SDLPowerUp.h"
#include "SDLBackground.h"
#include "SDLHUD.h"
#include "SDLText.h"
#include "SDLButton.h"
#include "SDLTextbox.h"
#include "SDLSlider.h"
#include "SDLCheckbox.h"
#include "SDLMessagebox.h"
#include "SDLMusicPlayer.h"
#include "SDLPicture.h"
#include "SDLAnimation.h"
#include "SDLRocket.h"
#include "SDLCursor.h"

namespace CCG_SDL
{
	/*
	 * SDL implementation of the game factory class
	 */
	class SDLFactory : public CCG::GameFactory
	{
		public:
			SDLFactory(void);
			SDLFactory(int width, int height);
			virtual ~SDLFactory(void);

			int initializeFactory(void);
			int releaseFactory(void);

			int loadAsset(void);

			CCG::Window* getWindow(void);
			CCG::EventStack* getEventStack(void);
			CCG::Cursor* getCursor(void);

			CCG::Timer* getTimer(void);
			CCG::Text* getText(std::string text, CCG::TextFont type);

			CCG::Car* getCar(CCG::CarType type);
			CCG::PowerUp* getPowerUp(CCG::PowerUpType type);
			CCG::Background* getBackground(CCG::BackgroundType type);
			CCG::HUD* getHUD(CCG::HUDType type);
			CCG::Button* getButton(CCG::ButtonType type);
			CCG::Textbox* getTextbox(CCG::TextboxType type);
			CCG::Slider* getSlider(CCG::SliderType type);
			CCG::Checkbox* getCheckbox(CCG::CheckboxType type);
			CCG::Messagebox* getMessagebox(CCG::MessageboxType type);
			CCG::Picture* getPicture(CCG::PictureType type);
			CCG::Animation* getAnimation(CCG::AnimationType type);
			CCG::Rocket* getRocket(CCG::RocketType type);

			CCG::MusicPlayer* getMusicPlayer(void);
			CCG::Music* getMusic(CCG::MusicType type);

		private:
			SDLAssetLib* assetLib;				//Library for all assets (textures, audio)
			SDLWindow* window;					//SDL window
			SDLEventStack* eventStack;			//SDL event stack
			SDLMusicPlayer* musicPlayer;		//SDL music player
			SDLCursor* cursor;					//SDL cursor
	};
}

#endif /* SDLENGINE_SDLFACTORY_H_ */

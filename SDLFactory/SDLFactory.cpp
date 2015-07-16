/*
 * SDLFactory.cpp
 *
 *  Created on: 9-mrt.-2015
 *      Author: Thomas
 */

#include "SDLFactory.h"

using namespace CCG_SDL;

SDLFactory::SDLFactory() : CCG::GameFactory()
{
	window = NULL;				//Rendering window
	cursor = NULL;				//Window cursor

	assetLib = new SDLAssetLib();
	eventStack = new SDLEventStack();
	musicPlayer = new SDLMusicPlayer();
}

SDLFactory::SDLFactory(int width, int height) : CCG::GameFactory(width, height)
{
	window = NULL;				//Rendering window
	cursor = NULL;				//Window cursor

	assetLib = new SDLAssetLib();
	eventStack = new SDLEventStack();
	musicPlayer = new SDLMusicPlayer();
}

SDLFactory::~SDLFactory()
{

}

int SDLFactory::initializeFactory()
{
	SDL_Window* newWindow;					//Rendering window
	SDL_Renderer* newRenderer;				//Window renderer

	//Initialize SDL
	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		return -1;
	}
	else
	{
		//Create window
		newWindow = SDL_CreateWindow(NULL, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, this->getScreenWidth(), this->getScreenHeight(), SDL_WINDOW_HIDDEN);
		if(newWindow == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			return -1;
		}
		else
		{
			//Create renderer
			newRenderer = SDL_CreateRenderer(newWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if(newRenderer == NULL)
			{
				printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
				return -1;
			}
			else
			{
				//Define window object
				window = new SDLWindow(newWindow, newRenderer);

				//Set-up asset library
				assetLib->setRenderer(newRenderer);

				//Initialize renderer color
				SDL_SetRenderDrawColor(newRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

				//Initialize PNG image loading
				int imgFlags = IMG_INIT_PNG;
				if(!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					return -1;
				}

				//Initialize true type font
				if(TTF_Init() == -1)
				{
					printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
					return -1;
				}

				//Initialize audio mixer
				if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
				{
					printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
					return -1;
				}

				//Allocate sound channels
				Mix_AllocateChannels(25);

				//Load basic start assets into the library
				if(assetLib->loadStartAssets() > 0)
				{
					printf("Start assets could not be loaded properly!\n");
					return -1;
				}

				//Set the window icon
				window->setIcon(assetLib->getIcon(ICON_WINDOW));

				//Hide system cursor
				SDL_ShowCursor(0);

				//Set game cursor
				SDLTexture** texturePack = new SDLTexture*[CCG::CURSOR_STATE_MAX]();

				texturePack[CCG::CURSOR_STATE_NORMAL] = assetLib->getTexture(TEXTURE_CURSOR01_NORMAL);
				texturePack[CCG::CURSOR_STATE_CLICK] = assetLib->getTexture(TEXTURE_CURSOR01_CLICK);

				cursor = new SDLCursor(window->getRenderer(), texturePack);

				delete(texturePack);
			}
		}
	}

	return 0;
}

int SDLFactory::releaseFactory()
{
	delete(musicPlayer);
	delete(cursor);
	delete(assetLib);
	delete(eventStack);
	delete(window);

	musicPlayer = NULL;
	assetLib = NULL;
	eventStack = NULL;
	window = NULL;

	//Quit SDL systems
	TTF_Quit();
	Mix_CloseAudio();
	Mix_Quit();
	IMG_Quit();
	SDL_Quit();

	return 0;
}

int SDLFactory::loadAsset()
{
	//Load textures
	if(assetLib->loadModels() != 0)
	{
		return -1;
	}

	//Load music
	if(assetLib->loadAudio() != 0)
	{
		return -1;
	}

	//Load fonts
	if(assetLib->loadFonts() != 0)
	{
		return -1;
	}

	return 0;
}

CCG::Cursor* SDLFactory::getCursor()
{
	return this->cursor;
}

CCG::Timer* SDLFactory::getTimer()
{
	return new SDLTimer();
}

CCG::Text* SDLFactory::getText(std::string text, CCG::TextFont type)
{
	SDLFont* font;

	switch(type)
	{
		case CCG::FONT_TEXT_SMALL:
			font = assetLib->getFont(FONT_TEXT_12);
			break;
		case CCG::FONT_TEXT_NORMAL:
			font = assetLib->getFont(FONT_TEXT_24);
			break;
		case CCG::FONT_TEXT_LARGE:
			font = assetLib->getFont(FONT_TEXT_42);
			break;
		case CCG::FONT_TITLE_SMALL:
			font = assetLib->getFont(FONT_TITLE_12);
			break;
		case CCG::FONT_TITLE_NORMAL:
			font = assetLib->getFont(FONT_TITLE_24);
			break;
		case CCG::FONT_TITLE_LARGE:
			font = assetLib->getFont(FONT_TITLE_42);
			break;
		case CCG::FONT_DISPLAY_SMALL:
			font = assetLib->getFont(FONT_DISPLAY_12);
			break;
		case CCG::FONT_DISPLAY_NORMAL:
			font = assetLib->getFont(FONT_DISPLAY_24);
			break;
		case CCG::FONT_DISPLAY_LARGE:
			font = assetLib->getFont(FONT_DISPLAY_42);
			break;
		default:
			font = assetLib->getFont(FONT_UNDEFINED);
			break;
	}

	SDLText* newText = new SDLText(window->getRenderer(), font, text);

	return newText;
}

CCG::Window* SDLFactory::getWindow()
{
	return this->window;
}

CCG::EventStack* SDLFactory::getEventStack()
{
	return this->eventStack;
}

CCG::Car* SDLFactory::getCar(CCG::CarType type)
{
	SDLTexture* texture;
	SDLSound* crashSound;

	switch(type)
	{
		case CCG::CAR_BLACK:
			texture = assetLib->getTexture(TEXTURE_CAR_BLACK);
			break;
		case CCG::CAR_BLUE:
			texture = assetLib->getTexture(TEXTURE_CAR_BLUE);
			break;
		case CCG::CAR_GREEN:
			texture = assetLib->getTexture(TEXTURE_CAR_GREEN);
			break;
		case CCG::CAR_PURPLE:
			texture = assetLib->getTexture(TEXTURE_CAR_PURPLE);
			break;
		case CCG::CAR_RED:
			texture = assetLib->getTexture(TEXTURE_CAR_RED);
			break;
		case CCG::CAR_YELLOW:
			texture = assetLib->getTexture(TEXTURE_CAR_YELLOW);
			break;
		case CCG::CAR_PLAYER_01:
			texture = assetLib->getTexture(TEXTURE_CAR_PLAYER_01);
			break;
		case CCG::CAR_PLAYER_02:
			texture = assetLib->getTexture(TEXTURE_CAR_PLAYER_02);
			break;
		case CCG::CAR_PLAYER_03:
			texture = assetLib->getTexture(TEXTURE_CAR_PLAYER_03);
			break;
		case CCG::CAR_PLAYER_04:
			texture = assetLib->getTexture(TEXTURE_CAR_PLAYER_04);
			break;
		case CCG::CAR_PLAYER_05:
			texture = assetLib->getTexture(TEXTURE_CAR_PLAYER_05);
			break;
		default:
			texture = assetLib->getTexture(TEXTURE_UNDEFINED);
			break;
	}

	crashSound = assetLib->getSound(SOUND_CRASH_CAR);

	SDLCar* newCar = new SDLCar(window->getRenderer(), texture, crashSound);

	return newCar;
}

CCG::PowerUp* SDLFactory::getPowerUp(CCG::PowerUpType type)
{
	SDLTexture* texture;
	CCG::PowerUpBonus bonus;

	switch(type)
	{
		case CCG::POWERUP_HEALTH:
			texture = assetLib->getTexture(TEXTURE_POWERUP_HEALTH);
			bonus = CCG::POWERUP_BONUS_HEALTH;
			break;
		case CCG::POWERUP_POINTS:
			texture = assetLib->getTexture(TEXTURE_POWERUP_POINTS);
			bonus = CCG::POWERUP_BONUS_POINTS;
			break;
		case CCG::POWERUP_INVINCIBILITY:
			texture = assetLib->getTexture(TEXTURE_POWERUP_INVINCIBILITY);
			bonus = CCG::POWERUP_BONUS_INVINCIBILITY;
			break;
		case CCG::POWERUP_ROCKETS:
			texture = assetLib->getTexture(TEXTURE_POWERUP_ROCKETS);
			bonus = CCG::POWERUP_BONUS_ROCKETS;
			break;
		default:
			texture = assetLib->getTexture(TEXTURE_UNDEFINED);
			bonus = CCG::POWERUP_BONUS_HEALTH;
			break;
	}

	SDLPowerUp* newPowerUp = new SDLPowerUp(window->getRenderer(), texture, bonus);

	return newPowerUp;
}

CCG::Background* SDLFactory::getBackground(CCG::BackgroundType type)
{
	SDLTexture* texture;
	CCG::ScrollDirection direction;

	switch(type)
	{
		case CCG::BACKGROUND_MENU:
			texture = assetLib->getTexture(TEXTURE_BACKGROUND_MENU);
			direction = CCG::SCROLL_DIAGONAL_FIRST;
			break;
		case CCG::BACKGROUND_MAP_CITY:
			texture = assetLib->getTexture(TEXTURE_BACKGROUND_CITY);
			direction = CCG::SCROLL_VERTICAL;
			break;
		case CCG::BACKGROUND_MAP_COUNTRYSIDE:
			texture = assetLib->getTexture(TEXTURE_BACKGROUND_COUNTRYSIDE);
			direction = CCG::SCROLL_HORIZONTAL;
			break;
		default:
			texture = assetLib->getTexture(TEXTURE_UNDEFINED);
			direction = CCG::SCROLL_OFF;
			break;
	}

	SDLBackground* newBackground = new SDLBackground(window->getRenderer(), texture, direction);

	return newBackground;
}

CCG::HUD* SDLFactory::getHUD(CCG::HUDType type)
{
	SDLTexture** texturePack = new SDLTexture*[HUD_ELEMENT_MAX]();
	SDLFont* nameFont = assetLib->getFont(FONT_TEXT_24);
	SDLFont* scoreFont = assetLib->getFont(FONT_DISPLAY_12);
	SDLFont* rocketsFont = assetLib->getFont(FONT_DISPLAY_24);
	SDLText* playerNameText = new SDLText(window->getRenderer(), nameFont, "");
	SDLText* playerScoreText = new SDLText(window->getRenderer(), scoreFont, "");
	SDLText* rocketsText = new SDLText(window->getRenderer(), rocketsFont, "");
	SDLHUD* newHUD;

	switch(type)
	{
		case CCG::HUD_01:
			texturePack[HUD_ELEMENT_STATUSBAR] = assetLib->getTexture(TEXTURE_STATUSBAR);
			texturePack[HUD_ELEMENT_HEALTHBAR] = assetLib->getTexture(TEXTURE_HEALTHBAR);
			texturePack[HUD_ELEMENT_NITROBAR] = assetLib->getTexture(TEXTURE_NITROBAR);
			texturePack[HUD_ELEMENT_INVINCIBILITY_STATUS] = assetLib->getTexture(TEXTURE_INVINCIBILITY_INDICATOR);
			texturePack[HUD_ELEMENT_PLAYER01_STATUS] = assetLib->getTexture(TEXTURE_PLAYERSTATUS_RED);
			texturePack[HUD_ELEMENT_PLAYER02_STATUS] = assetLib->getTexture(TEXTURE_PLAYERSTATUS_GREEN);
			texturePack[HUD_ELEMENT_PLAYER03_STATUS] = assetLib->getTexture(TEXTURE_PLAYERSTATUS_YELLOW);
			texturePack[HUD_ELEMENT_PLAYER04_STATUS] = assetLib->getTexture(TEXTURE_PLAYERSTATUS_PURPLE);
			texturePack[HUD_ELEMENT_ROCKETS] = assetLib->getTexture(TEXTURE_ROCKET_01);
			break;
		default:
			texturePack[HUD_ELEMENT_STATUSBAR] = assetLib->getTexture(TEXTURE_UNDEFINED);
			texturePack[HUD_ELEMENT_HEALTHBAR] = assetLib->getTexture(TEXTURE_UNDEFINED);
			texturePack[HUD_ELEMENT_NITROBAR] = assetLib->getTexture(TEXTURE_UNDEFINED);
			texturePack[HUD_ELEMENT_INVINCIBILITY_STATUS] = assetLib->getTexture(TEXTURE_UNDEFINED);
			texturePack[HUD_ELEMENT_PLAYER01_STATUS] = assetLib->getTexture(TEXTURE_UNDEFINED);
			texturePack[HUD_ELEMENT_PLAYER02_STATUS] = assetLib->getTexture(TEXTURE_UNDEFINED);
			texturePack[HUD_ELEMENT_PLAYER03_STATUS] = assetLib->getTexture(TEXTURE_UNDEFINED);
			texturePack[HUD_ELEMENT_PLAYER04_STATUS] = assetLib->getTexture(TEXTURE_UNDEFINED);
			texturePack[HUD_ELEMENT_ROCKETS] = assetLib->getTexture(TEXTURE_UNDEFINED);
			break;
	}

	newHUD = new SDLHUD(window->getRenderer(), texturePack, playerNameText, playerScoreText, rocketsText);

	delete(texturePack);

	return newHUD;
}

CCG::Button* SDLFactory::getButton(CCG::ButtonType type)
{
	SDLTexture** texturePack = new SDLTexture*[CCG::GAMEBUTTON_MAX]();
	SDLSound* clickSound;
	SDLButton* newButton;

	switch(type)
	{
		case CCG::BUTTON_01:
			texturePack[CCG::GAMEBUTTON_NORMAL] = assetLib->getTexture(TEXTURE_BUTTON01_NORMAL);
			texturePack[CCG::GAMEBUTTON_PRESSED] = assetLib->getTexture(TEXTURE_BUTTON01_PRESSED);
			texturePack[CCG::GAMEBUTTON_HIGHLIGHTED] = assetLib->getTexture(TEXTURE_BUTTON01_HIGHLIGHTED);
			texturePack[CCG::GAMEBUTTON_INACTIVE] = assetLib->getTexture(TEXTURE_BUTTON01_INACTIVE);
			clickSound = assetLib->getSound(SOUND_BUTTON_CLICK);
			break;
		default:
			texturePack[CCG::GAMEBUTTON_NORMAL] = assetLib->getTexture(TEXTURE_UNDEFINED);
			texturePack[CCG::GAMEBUTTON_PRESSED] = assetLib->getTexture(TEXTURE_UNDEFINED);
			texturePack[CCG::GAMEBUTTON_HIGHLIGHTED] = assetLib->getTexture(TEXTURE_UNDEFINED);
			texturePack[CCG::GAMEBUTTON_INACTIVE] = assetLib->getTexture(TEXTURE_UNDEFINED);
			clickSound = assetLib->getSound(SOUND_UNDEFINED);
			break;
	}

	newButton = new SDLButton(window->getRenderer(), texturePack, clickSound);

	delete(texturePack);

	return newButton;
}

CCG::Textbox* SDLFactory::getTextbox(CCG::TextboxType type)
{
	SDLTexture** texturePack = new SDLTexture*[CCG::TEXTBOX_STATE_MAX]();
	SDLText* textFont;
	SDLTextbox* newTextbox;

	switch(type)
	{
		case CCG::TEXTBOX_01:
			texturePack[CCG::TEXTBOX_STATE_NORMAL] = assetLib->getTexture(TEXTURE_TEXTBOX01_NORMAL);
			texturePack[CCG::TEXTBOX_STATE_ACTIVE] = assetLib->getTexture(TEXTURE_TEXTBOX01_ACTIVE);
			texturePack[CCG::TEXTBOX_STATE_HIGHLIGHTED] = assetLib->getTexture(TEXTURE_TEXTBOX01_HIGHLIGHTED);
			textFont = new SDLText(window->getRenderer(), assetLib->getFont(FONT_TEXT_42), "");
			textFont->setColor(255, 255, 255, 0);
			break;
		default:
			texturePack[CCG::TEXTBOX_STATE_NORMAL] = assetLib->getTexture(TEXTURE_UNDEFINED);
			texturePack[CCG::TEXTBOX_STATE_ACTIVE] = assetLib->getTexture(TEXTURE_UNDEFINED);
			texturePack[CCG::TEXTBOX_STATE_HIGHLIGHTED] = assetLib->getTexture(TEXTURE_UNDEFINED);
			textFont = new SDLText(window->getRenderer(), assetLib->getFont(FONT_UNDEFINED), "");
			break;
	}

	newTextbox = new SDLTextbox(window->getRenderer(), textFont, texturePack);

	delete(texturePack);

	return newTextbox;
}

CCG::Slider* SDLFactory::getSlider(CCG::SliderType type)
{
	SDLTexture** texturePack = new SDLTexture*[SLIDER_ELEMENT_MAX]();
	SDLSlider* newSlider;

	switch(type)
	{
		case CCG::SLIDER_01:
			texturePack[SLIDER_ELEMENT_BAR] = assetLib->getTexture(TEXTURE_SLIDER01_BAR);
			texturePack[SLIDER_ELEMENT_MARKER] = assetLib->getTexture(TEXTURE_SLIDER01_MARKER);
			break;
		default:
			texturePack[SLIDER_ELEMENT_BAR] = assetLib->getTexture(TEXTURE_UNDEFINED);
			texturePack[SLIDER_ELEMENT_MARKER] = assetLib->getTexture(TEXTURE_UNDEFINED);
			break;
	}

	newSlider = new SDLSlider(window->getRenderer(), texturePack);

	delete(texturePack);

	return newSlider;
}

CCG::Checkbox* SDLFactory::getCheckbox(CCG::CheckboxType type)
{
	SDLTexture** texturePack = new SDLTexture*[CHECKBOX_ELEMENT_MAX]();
	SDLCheckbox* newCheckbox;

	switch(type)
	{
		case CCG::CHECKBOX_01:
			texturePack[CHECKBOX_ELEMENT_NORMAL] = assetLib->getTexture(TEXTURE_CHECKBOX01_NORMAL);
			texturePack[CHECKBOX_ELEMENT_HIGHLIGHTED] = assetLib->getTexture(TEXTURE_CHECKBOX01_HIGHLIGHTED);
			texturePack[CHECKBOX_ELEMENT_CHECKTICK] = assetLib->getTexture(TEXTURE_CHECKBOX01_TICK);
			break;
		default:
			texturePack[CHECKBOX_ELEMENT_NORMAL] = assetLib->getTexture(TEXTURE_UNDEFINED);
			texturePack[CHECKBOX_ELEMENT_HIGHLIGHTED] = assetLib->getTexture(TEXTURE_UNDEFINED);
			texturePack[CHECKBOX_ELEMENT_CHECKTICK] = assetLib->getTexture(TEXTURE_UNDEFINED);
			break;
	}

	newCheckbox = new SDLCheckbox(window->getRenderer(), texturePack);

	delete(texturePack);

	return newCheckbox;
}

CCG::Messagebox* SDLFactory::getMessagebox(CCG::MessageboxType type)
{
	SDLTexture* textureBackground;
	SDLButton* button;
	SDLText* messageText;
	SDLText* buttonText;
	SDLMessagebox* newMessagebox;

	switch(type)
	{
		case CCG::MESSAGEBOX_01:
			textureBackground = assetLib->getTexture(TEXTURE_MESSAGEBOX01_BACKGROUND);
			button = (SDLButton*)this->getButton(CCG::BUTTON_01);
			messageText = new SDLText(window->getRenderer(), assetLib->getFont(FONT_TEXT_42), "");
			messageText->setColor(255, 255, 255, 0);
			buttonText = new SDLText(window->getRenderer(), assetLib->getFont(FONT_TEXT_42), "");
			buttonText->setColor(255, 255, 255, 0);
			break;
		default:
			textureBackground = assetLib->getTexture(TEXTURE_UNDEFINED);
			button = (SDLButton*)this->getButton(CCG::BUTTON_MAX);
			messageText = new SDLText(window->getRenderer(), assetLib->getFont(FONT_UNDEFINED), "");
			messageText->setColor(255, 255, 255, 0);
			buttonText = new SDLText(window->getRenderer(), assetLib->getFont(FONT_UNDEFINED), "");
			buttonText->setColor(255, 255, 255, 0);
			break;
	}

	newMessagebox = new SDLMessagebox(window->getRenderer(), textureBackground, button, messageText, buttonText, NULL, NULL, NULL);

	return newMessagebox;
}

CCG::Picture* SDLFactory::getPicture(CCG::PictureType type)
{
	SDLTexture* texture;
	SDLPicture* newPicture;

	switch(type)
	{
		case CCG::PICTURE_SPLASHART:
			texture = assetLib->getTexture(TEXTURE_SPLASH);
			break;
		case CCG::PICTURE_STARTLOGO:
			texture = assetLib->getTexture(TEXTURE_STARTLOGO);
			break;
		case CCG::PICTURE_CAR_01_TOP:
			texture = assetLib->getTexture(TEXTURE_CAR_PLAYER_01);
			break;
		case CCG::PICTURE_CAR_02_TOP:
			texture = assetLib->getTexture(TEXTURE_CAR_PLAYER_02);
			break;
		case CCG::PICTURE_CAR_03_TOP:
			texture = assetLib->getTexture(TEXTURE_CAR_PLAYER_03);
			break;
		case CCG::PICTURE_CAR_04_TOP:
			texture = assetLib->getTexture(TEXTURE_CAR_PLAYER_04);
			break;
		case CCG::PICTURE_CAR_05_TOP:
			texture = assetLib->getTexture(TEXTURE_CAR_PLAYER_05);
			break;
		default:
			texture = assetLib->getTexture(TEXTURE_UNDEFINED);
			break;
	}

	newPicture = new SDLPicture(window->getRenderer(), texture);

	return newPicture;
}

CCG::Animation* SDLFactory::getAnimation(CCG::AnimationType type)
{
	SDLTexture* texture;
	SDLAnimation* newAnimation;
	int spriteWidth, spriteHeight = 0;
	int animationRows, animationColumns = 0;
	float animationNextFrameTime = 0.0f;

	switch(type)
	{
		case CCG::ANIMATION_EXPLOSION:
			texture = assetLib->getTexture(TEXTURE_ANIMATION_EXPLOSION_01);
			spriteWidth = 96;
			spriteHeight = 96;
			animationRows = 4;
			animationColumns = 5;
			animationNextFrameTime = 0.05;
			break;
		default:
			texture = assetLib->getTexture(TEXTURE_UNDEFINED);
			break;
	}

	newAnimation = new SDLAnimation(window->getRenderer(), texture, spriteWidth, spriteHeight, animationRows, animationColumns, animationNextFrameTime);

	return newAnimation;
}

CCG::Rocket* SDLFactory::getRocket(CCG::RocketType type)
{
	SDLTexture* texture;
	SDLSound* sound;
	SDLRocket* newRocket;

	switch(type)
	{
		case CCG::ROCKET_01:
			texture = assetLib->getTexture(TEXTURE_ROCKET_01);
			sound = assetLib->getSound(SOUND_ROCKET_FIRE);
			break;
		default:
			texture = assetLib->getTexture(TEXTURE_UNDEFINED);
			sound = assetLib->getSound(SOUND_UNDEFINED);
			break;
	}

	newRocket = new SDLRocket(window->getRenderer(), texture, sound);

	return newRocket;
}

CCG::MusicPlayer* SDLFactory::getMusicPlayer()
{
	return (CCG::MusicPlayer*)this->musicPlayer;
}

CCG::Music* SDLFactory::getMusic(CCG::MusicType type)
{
	SDLMusic* music;

	switch(type)
	{
		case CCG::MUSIC_START:
			music = assetLib->getMusic(MUSIC_START);
			break;
		case CCG::MUSIC_MENU:
			music = assetLib->getMusic(MUSIC_MENU);
			break;
		case CCG::MUSIC_OPTIONS:
			music = assetLib->getMusic(MUSIC_OPTIONS);
			break;
		case CCG::MUSIC_RADIO01:
			music = assetLib->getMusic(MUSIC_RADIO01);
			break;
		default:
			music = assetLib->getMusic(MUSIC_UNDEFINED);
			break;
	}

	return music;
}

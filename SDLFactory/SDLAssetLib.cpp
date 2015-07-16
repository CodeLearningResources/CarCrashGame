/*
 * SDLAssetLib.cpp
 *
 *  Created on: 22-mrt.-2015
 *      Author: Thomas
 */

#include "SDLAssetLib.h"

using namespace CCG_SDL;

SDLAssetLib::SDLAssetLib()
{
	renderer = NULL;
	textures = new SDLTexture*[TEXTURE_MAX]();
	music = new SDLMusic*[MUSIC_MAX]();
	sound = new SDLSound*[SOUND_MAX]();
	fonts = new SDLFont*[FONT_MAX]();
	icons = new SDL_Surface*[ICON_MAX]();
}

SDLAssetLib::SDLAssetLib(SDL_Renderer* renderer)
{
	this->renderer = renderer;
	textures = new SDLTexture*[TEXTURE_MAX]();
	music = new SDLMusic*[MUSIC_MAX]();
	sound = new SDLSound*[SOUND_MAX]();
	fonts = new SDLFont*[FONT_MAX]();
	icons= new SDL_Surface*[ICON_MAX]();
}

SDLAssetLib::~SDLAssetLib()
{
	unloadStartAssets();
	unloadModels();
	unloadAudio();
	unloadFonts();

	textures = NULL;
	music = NULL;
	sound = NULL;
	fonts = NULL;
	icons = NULL;
}

void SDLAssetLib::setRenderer(SDL_Renderer* renderer)
{
	this->renderer = renderer;
}

SDLTexture* SDLAssetLib::loadTexture(std::string filename)
{
	int textureWidth = 0;
	int textureHeight = 0;

	//The final texture
	SDL_Texture* texture = NULL;

	//Loaded image
	SDL_Surface* loadedImage = IMG_Load(filename.c_str());

	if(loadedImage != NULL && renderer != NULL)
	{
		//Create texture from surface pixels
		texture = SDL_CreateTextureFromSurface(renderer, loadedImage);

		if(texture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", filename.c_str(), SDL_GetError());
		}
		else
		{
			textureWidth = loadedImage->w;
			textureHeight = loadedImage->h;
		}

		//Free old image
		SDL_FreeSurface(loadedImage);
	}
	else
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", filename.c_str(), IMG_GetError());
	}

	return new SDLTexture(texture, textureWidth, textureHeight);
}

SDLMusic* SDLAssetLib::loadMusic(std::string filename)
{
	//Loaded music
	Mix_Music* musicFile = Mix_LoadMUS(filename.c_str());

	if(musicFile == NULL)
	{
		printf("Unable to load music %s! Mix_Music Error: %s\n", filename.c_str(), Mix_GetError());
	}

	return new SDLMusic(musicFile);
}

SDLSound* SDLAssetLib::loadSound(std::string filename)
{
	//Loaded sound
	Mix_Chunk* soundFile = Mix_LoadWAV(filename.c_str());

	if(soundFile == NULL)
	{
		printf("Unable to load audio %s! Mix_Music Error: %s\n", filename.c_str(), Mix_GetError());
	}

	return new SDLSound(soundFile);
}

SDLFont* SDLAssetLib::loadFont(std::string filename, int fontSize)
{
	//Loaded font
	TTF_Font* newFont = TTF_OpenFont(filename.c_str(), fontSize);

	if(newFont == NULL)
	{
		printf("Unable to load font %s! TTF_Font Error: %s\n", filename.c_str(), TTF_GetError());
	}

	return new SDLFont(newFont);
}

int SDLAssetLib::loadStartAssets()
{
	int errors = 0;

	//Load window icon
	icons[ICON_WINDOW] = IMG_Load("Sprites/CarCrashIcon.png");

	//Check if icon is loaded correctly
	if(icons[ICON_WINDOW] == NULL)
	{
		errors++;

		printf("Error in load procedure, the window icon is not loaded!\n");
	}

	//Load cursor
	textures[TEXTURE_CURSOR01_NORMAL] = loadTexture("Sprites/Cursor01_NORMAL.png");
	textures[TEXTURE_CURSOR01_CLICK] = loadTexture("Sprites/Cursor01_CLICK.png");

	//Check if cursor is loaded correctly
	if(textures[TEXTURE_CURSOR01_NORMAL] == NULL || textures[TEXTURE_CURSOR01_CLICK] == NULL)
	{
		errors++;

		printf("Error in load procedure, the cursor is not loaded!\n");
	}

	//Load splash texture
	textures[TEXTURE_SPLASH] = loadTexture("Sprites/splash.png");

	//Check if texture is loaded correctly
	if(textures[TEXTURE_SPLASH] == NULL)
	{
		errors++;

		printf("Error in load procedure, splash texture is not loaded!\n");
	}
	else if(textures[TEXTURE_SPLASH]->getTexture() == NULL)
	{
		errors++;
	}

	return errors;
}

int SDLAssetLib::unloadStartAssets()
{
	//Unload window icon
	SDL_FreeSurface(icons[ICON_WINDOW]);
	icons[ICON_WINDOW] = NULL;

	//Unload splash texture
	delete(textures[TEXTURE_SPLASH]);
	textures[TEXTURE_SPLASH] = NULL;

	return 0;
}

int SDLAssetLib::loadModels()
{
	int i;
	int errors = 0;

	//Load textures
	//Buttons
	textures[TEXTURE_BUTTON01_NORMAL] = loadTexture("Sprites/BUTTON01_NORMAL.png");
	textures[TEXTURE_BUTTON01_PRESSED] = loadTexture("Sprites/BUTTON01_PRESSED.png");
	textures[TEXTURE_BUTTON01_HIGHLIGHTED] = loadTexture("Sprites/BUTTON01_HIGHLIGHTED.png");
	textures[TEXTURE_BUTTON01_INACTIVE] = loadTexture("Sprites/BUTTON01_INACTIVE.png");

	//Textboxes
	textures[TEXTURE_TEXTBOX01_NORMAL] = loadTexture("Sprites/TEXTBOX01_NORMAL.png");
	textures[TEXTURE_TEXTBOX01_ACTIVE] = loadTexture("Sprites/TEXTBOX01_ACTIVE.png");
	textures[TEXTURE_TEXTBOX01_HIGHLIGHTED] = loadTexture("Sprites/TEXTBOX01_HIGHLIGHTED.png");

	//Sliders
	textures[TEXTURE_SLIDER01_BAR] = loadTexture("Sprites/SLIDER01_BAR.png");
	textures[TEXTURE_SLIDER01_MARKER] = loadTexture("Sprites/SLIDER01_MARKER.png");

	//Checkbox
	textures[TEXTURE_CHECKBOX01_NORMAL] = loadTexture("Sprites/CHECKBOX01_NORMAL.png");
	textures[TEXTURE_CHECKBOX01_HIGHLIGHTED] = loadTexture("Sprites/CHECKBOX01_HIGHLIGHTED.png");
	textures[TEXTURE_CHECKBOX01_TICK] = loadTexture("Sprites/CHECKBOX01_TICK.png");

	//Messagebox
	textures[TEXTURE_MESSAGEBOX01_BACKGROUND] = loadTexture("Sprites/MESSAGEBOX01.png");

	//Pictures
	textures[TEXTURE_STARTLOGO] = loadTexture("Sprites/CarCrashTitle.png");

	//Cars
	textures[TEXTURE_CAR_BLACK] = loadTexture("Sprites/CAR_BLACK.png");
	textures[TEXTURE_CAR_BLUE] = loadTexture("Sprites/CAR_BLUE.png");
	textures[TEXTURE_CAR_GREEN] = loadTexture("Sprites/CAR_GREEN.png");
	textures[TEXTURE_CAR_PURPLE] = loadTexture("Sprites/CAR_PURPLE.png");
	textures[TEXTURE_CAR_RED] = loadTexture("Sprites/CAR_RED.png");
	textures[TEXTURE_CAR_YELLOW] = loadTexture("Sprites/CAR_YELLOW.png");
	textures[TEXTURE_CAR_PLAYER_01] = loadTexture("Sprites/CAR_PLAYER_01.png");
	textures[TEXTURE_CAR_PLAYER_02] = loadTexture("Sprites/CAR_PLAYER_02.png");
	textures[TEXTURE_CAR_PLAYER_03] = loadTexture("Sprites/CAR_PLAYER_03.png");
	textures[TEXTURE_CAR_PLAYER_04] = loadTexture("Sprites/CAR_PLAYER_04.png");
	textures[TEXTURE_CAR_PLAYER_05] = loadTexture("Sprites/CAR_PLAYER_05.png");

	//Power-ups
	textures[TEXTURE_POWERUP_HEALTH] = loadTexture("Sprites/POWERUP_HEALTH.png");
	textures[TEXTURE_POWERUP_POINTS] = loadTexture("Sprites/POWERUP_POINTS.png");
	textures[TEXTURE_POWERUP_INVINCIBILITY] = loadTexture("Sprites/POWERUP_INVINCIBILITY.png");
	textures[TEXTURE_POWERUP_ROCKETS] = loadTexture("Sprites/POWERUP_ROCKETS.png");

	//Backgrounds
	textures[TEXTURE_BACKGROUND_MENU] = loadTexture("Sprites/MenuBackground.png");
	textures[TEXTURE_BACKGROUND_CITY] = loadTexture("Sprites/roadTexture01.png");
	textures[TEXTURE_BACKGROUND_COUNTRYSIDE] = loadTexture("Sprites/roadTexture02.png");

	//Animations
	textures[TEXTURE_ANIMATION_EXPLOSION_01] = loadTexture("Sprites/explosionAnimSprite.png");

	//Rockets
	textures[TEXTURE_ROCKET_01] = loadTexture("Sprites/Rocket01.png");

	//HUD
	textures[TEXTURE_STATUSBAR] = loadTexture("Sprites/Statusbar.png");
	textures[TEXTURE_HEALTHBAR] = loadTexture("Sprites/HealthbarForeColor.png");
	textures[TEXTURE_NITROBAR] = loadTexture("Sprites/NitrobarForeColor.png");
	textures[TEXTURE_INVINCIBILITY_INDICATOR] = loadTexture("Sprites/HUD_INVINCIBILITY.png");
	textures[TEXTURE_PLAYERSTATUS_RED] = loadTexture("Sprites/PlayerHUDRed.png");
	textures[TEXTURE_PLAYERSTATUS_GREEN] = loadTexture("Sprites/PlayerHUDGreen.png");
	textures[TEXTURE_PLAYERSTATUS_YELLOW] = loadTexture("Sprites/PlayerHUDYellow.png");
	textures[TEXTURE_PLAYERSTATUS_PURPLE] = loadTexture("Sprites/PlayerHUDPurple.png");

	//Check if every model is loaded correctly
	for(i = 0; i < TEXTURE_MAX; i++)
	{
		if(textures[i] == NULL)
		{
			errors++;

			printf("Error in load procedure, model %d is not loaded!\n", i);
		}
		else if(textures[i]->getTexture() == NULL)
		{
			errors++;
		}
	}

	return errors;
}

int SDLAssetLib::unloadModels()
{
	int i;

	//Unload textures
	for(i = 0; i < TEXTURE_MAX; i++)
	{
		if(textures[i] != NULL)
		{
			delete(textures[i]);
			textures[i] = NULL;
		}
	}

	return 0;
}

int SDLAssetLib::loadAudio()
{
	int i;
	int errors = 0;

	//Load music
	music[MUSIC_START] = loadMusic("Sound/START.mp3");
	music[MUSIC_MENU] = loadMusic("Sound/MENU.mp3");
	music[MUSIC_OPTIONS] = loadMusic("Sound/OPTIONS.mp3");
	music[MUSIC_RADIO01] = loadMusic("Sound/GAMEMUSIC01.mp3");

	//Load sound
	sound[SOUND_CRASH_CAR] = loadSound("Sound/CrashCar.wav");
	sound[SOUND_BUTTON_CLICK] = loadSound("Sound/ButtonClick.wav");
	sound[SOUND_ROCKET_FIRE] = loadSound("Sound/RocketFire.wav");

	//Check if every music file is loaded correctly
	for(i = 0; i < MUSIC_MAX; i++)
	{
		if(music[i] == NULL)
		{
			errors++;

			printf("Error in load procedure, music %d is not loaded!\n", i);
		}
		else if(music[i]->getMusic() == NULL)
		{
			errors++;
		}
	}

	//Check if every audio file is loaded correctly
	for(i = 0; i < SOUND_MAX; i++)
	{
		if(sound[i] == NULL)
		{
			errors++;

			printf("Error in load procedure, sound %d is not loaded!\n", i);
		}
		else if(sound[i]->getSound() == NULL)
		{
			errors++;
		}
	}

	return errors;
}

int SDLAssetLib::unloadAudio()
{
	int i;

	//Unload music files
	for(i = 0; i < MUSIC_MAX; i++)
	{
		if(music[i] != NULL)
		{
			delete(music[i]);
			music[i] = NULL;
		}
	}

	//Unload sound files
	for(i = 0; i < SOUND_MAX; i++)
	{
		if(sound[i] != NULL)
		{
			delete(sound[i]);
			sound[i] = NULL;
		}
	}

	return 0;
}

int SDLAssetLib::loadFonts()
{
	int i;
	int errors = 0;

	//Load fonts
	fonts[FONT_TEXT_12] = loadFont("Fonts/frquad.ttf", 12);
	fonts[FONT_TEXT_24] = loadFont("Fonts/frquad.ttf", 24);
	fonts[FONT_TEXT_42] = loadFont("Fonts/frquad.ttf", 42);

	fonts[FONT_TITLE_12] = loadFont("Fonts/QoC.ttf", 12);
	fonts[FONT_TITLE_24] = loadFont("Fonts/QoC.ttf", 24);
	fonts[FONT_TITLE_42] = loadFont("Fonts/QoC.ttf", 42);

	fonts[FONT_DISPLAY_12] = loadFont("Fonts/24Display.ttf", 12);
	fonts[FONT_DISPLAY_24] = loadFont("Fonts/24Display.ttf", 24);
	fonts[FONT_DISPLAY_42] = loadFont("Fonts/24Display.ttf", 42);

	//Check if every font is loaded correctly
	for(i = 0; i < FONT_MAX; i++)
	{
		if(fonts[i] == NULL)
		{
			errors++;

			printf("Error in load procedure, font %d is not loaded!\n", i);
		}
		else if(fonts[i]->getFont() == NULL)
		{
			errors++;
		}
	}

	return errors;
}

int SDLAssetLib::unloadFonts()
{
	int i;

	//Unload fonts
	for(i = 0; i < FONT_MAX; i++)
	{
		if(fonts[i] != NULL)
		{
			delete(fonts[i]);
			fonts[i] = NULL;
		}
	}

	return 0;
}

SDLTexture* SDLAssetLib::getTexture(TextureType texture)
{
	if(texture > TEXTURE_UNDEFINED && texture < TEXTURE_MAX)
	{
		return this->textures[texture];
	}
	else
	{
		return NULL;
	}
}

SDLMusic* SDLAssetLib::getMusic(MusicType music)
{
	if(music > MUSIC_UNDEFINED && music < MUSIC_MAX)
	{
		return this->music[music];
	}
	else
	{
		return NULL;
	}
}

SDLSound* SDLAssetLib::getSound(SoundType sound)
{
	if(sound > SOUND_UNDEFINED && sound < SOUND_MAX)
	{
		return this->sound[sound];
	}
	else
	{
		return NULL;
	}
}

SDLFont* SDLAssetLib::getFont(FontType font)
{
	if(font > FONT_UNDEFINED && font < FONT_MAX)
	{
		return this->fonts[font];
	}
	else
	{
		return NULL;
	}
}

SDL_Surface* SDLAssetLib::getIcon(IconType icon)
{
	if(icon > ICON_UNDEFINED && icon < ICON_MAX)
	{
		return this->icons[icon];
	}
	else
	{
		return NULL;
	}
}

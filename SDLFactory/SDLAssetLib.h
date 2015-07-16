/*
 * SDLAssetLib.h
 *
 *  Created on: 22-mrt.-2015
 *      Author: Thomas
 */

#ifndef SDLENGINE_SDLASSETLIB_H_
#define SDLENGINE_SDLASSETLIB_H_

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

#include "SDLTexture.h"
#include "SDLMusic.h"
#include "SDLSound.h"
#include "SDLFont.h"

namespace CCG_SDL
{
	enum TextureType
	{
		TEXTURE_UNDEFINED = -1,
		TEXTURE_SPLASH,
		TEXTURE_STARTLOGO,
		TEXTURE_BACKGROUND_MENU,
		TEXTURE_BACKGROUND_CITY,
		TEXTURE_BACKGROUND_COUNTRYSIDE,
		TEXTURE_BUTTON01_NORMAL,
		TEXTURE_BUTTON01_PRESSED,
		TEXTURE_BUTTON01_HIGHLIGHTED,
		TEXTURE_BUTTON01_INACTIVE,
		TEXTURE_TEXTBOX01_NORMAL,
		TEXTURE_TEXTBOX01_ACTIVE,
		TEXTURE_TEXTBOX01_HIGHLIGHTED,
		TEXTURE_SLIDER01_BAR,
		TEXTURE_SLIDER01_MARKER,
		TEXTURE_CHECKBOX01_NORMAL,
		TEXTURE_CHECKBOX01_HIGHLIGHTED,
		TEXTURE_CHECKBOX01_TICK,
		TEXTURE_MESSAGEBOX01_BACKGROUND,
		TEXTURE_CAR_BLACK,
		TEXTURE_CAR_BLUE,
		TEXTURE_CAR_GREEN,
		TEXTURE_CAR_PURPLE,
		TEXTURE_CAR_RED,
		TEXTURE_CAR_YELLOW,
		TEXTURE_CAR_PLAYER_01,
		TEXTURE_CAR_PLAYER_02,
		TEXTURE_CAR_PLAYER_03,
		TEXTURE_CAR_PLAYER_04,
		TEXTURE_CAR_PLAYER_05,
		TEXTURE_POWERUP_HEALTH,
		TEXTURE_POWERUP_POINTS,
		TEXTURE_POWERUP_INVINCIBILITY,
		TEXTURE_POWERUP_ROCKETS,
		TEXTURE_STATUSBAR,
		TEXTURE_HEALTHBAR,
		TEXTURE_NITROBAR,
		TEXTURE_INVINCIBILITY_INDICATOR,
		TEXTURE_PLAYERSTATUS_RED,
		TEXTURE_PLAYERSTATUS_GREEN,
		TEXTURE_PLAYERSTATUS_YELLOW,
		TEXTURE_PLAYERSTATUS_PURPLE,
		TEXTURE_ANIMATION_EXPLOSION_01,
		TEXTURE_ROCKET_01,
		TEXTURE_CURSOR01_NORMAL,
		TEXTURE_CURSOR01_CLICK,
		TEXTURE_MAX
	};

	enum MusicType
	{
		MUSIC_UNDEFINED = -1,
		MUSIC_START,
		MUSIC_MENU,
		MUSIC_OPTIONS,
		MUSIC_RADIO01,
		MUSIC_MAX
	};

	enum SoundType
	{
		SOUND_UNDEFINED = -1,
		SOUND_CRASH_CAR,
		SOUND_BUTTON_CLICK,
		SOUND_ROCKET_FIRE,
		SOUND_MAX
	};

	enum FontType
	{
		FONT_UNDEFINED = -1,
		FONT_TEXT_12,
		FONT_TEXT_24,
		FONT_TEXT_42,
		FONT_TITLE_12,
		FONT_TITLE_24,
		FONT_TITLE_42,
		FONT_DISPLAY_12,
		FONT_DISPLAY_24,
		FONT_DISPLAY_42,
		FONT_MAX
	};

	enum IconType
	{
		ICON_UNDEFINED = -1,
		ICON_WINDOW,
		ICON_MAX
	};

	/*
	 * Asset library for loading all in-game textures, fonts and sounds
	 */
	class SDLAssetLib
	{
		public:
			SDLAssetLib(void);
			SDLAssetLib(SDL_Renderer* renderer);
			virtual ~SDLAssetLib(void);

			void setRenderer(SDL_Renderer* renderer);

			int loadStartAssets(void);
			int unloadStartAssets(void);

			int loadModels(void);
			int unloadModels(void);

			int loadAudio(void);
			int unloadAudio(void);

			int loadFonts(void);
			int unloadFonts(void);

			SDLTexture* getTexture(TextureType texture);
			SDLMusic* getMusic(MusicType music);
			SDLSound* getSound(SoundType sound);
			SDLFont* getFont(FontType font);
			SDL_Surface* getIcon(IconType icon);

		private:
			SDL_Renderer* renderer;				//Window renderer

			//Textures
			SDLTexture** textures;

			//Music
			SDLMusic** music;

			//Sound
			SDLSound** sound;

			//Font
			SDLFont** fonts;

			//Window Icon
			SDL_Surface** icons;

			SDLTexture* loadTexture(std::string filename);
			SDLMusic* loadMusic(std::string filename);
			SDLSound* loadSound(std::string filename);
			SDLFont* loadFont(std::string filename, int fontSize);
	};
}

#endif /* SDLENGINE_SDLASSETLIB_H_ */

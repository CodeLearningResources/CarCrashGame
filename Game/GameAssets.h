/*
 * GameAssets.h
 *
 *  Created on: 28-mrt.-2015
 *      Author: Thomas
 */

#ifndef GAME_GAMEASSETS_H_
#define GAME_GAMEASSETS_H_

namespace CCG
{
	#define PLAYERCARS_MAX 5
	#define ENEMYCARS_MAX 6

	//All defined text fonts
	enum TextFont
	{
		FONT_TEXT_SMALL,
		FONT_TEXT_NORMAL,
		FONT_TEXT_LARGE,
		FONT_TITLE_SMALL,
		FONT_TITLE_NORMAL,
		FONT_TITLE_LARGE,
		FONT_DISPLAY_SMALL,
		FONT_DISPLAY_NORMAL,
		FONT_DISPLAY_LARGE,
		FONT_MAX
	};

	//All defined button types
	enum ButtonType
	{
		BUTTON_01,
		BUTTON_MAX
	};

	//All defined textbox types
	enum TextboxType
	{
		TEXTBOX_01,
		TEXTBOX_MAX
	};

	//All defined slider types
	enum SliderType
	{
		SLIDER_01,
		SLIDER_MAX
	};

	//All defined checkbox types
	enum CheckboxType
	{
		CHECKBOX_01,
		CHECKBOX_MAX
	};

	//All defined messagebox types
	enum MessageboxType
	{
		MESSAGEBOX_01,
		MESSAGEBOX_MAX
	};

	//All defined cursor types
	enum CursorType
	{
		CURSOR_01,
		CURSOR_MAX
	};

	//All defined car types
	enum CarType
	{
		CAR_BLACK,
		CAR_BLUE,
		CAR_GREEN,
		CAR_PURPLE,
		CAR_RED,
		CAR_YELLOW,
		CAR_PLAYER_01,
		CAR_PLAYER_02,
		CAR_PLAYER_03,
		CAR_PLAYER_04,
		CAR_PLAYER_05,
		CAR_MAX
	};

	//All defined power-up types
	enum PowerUpType
	{
		POWERUP_HEALTH,
		POWERUP_POINTS,
		POWERUP_INVINCIBILITY,
		POWERUP_ROCKETS,
		POWERUP_MAX
	};

	//All defined background types
	enum BackgroundType
	{
		BACKGROUND_MENU,
		BACKGROUND_MAP_CITY,
		BACKGROUND_MAP_COUNTRYSIDE,
		BACKGROUND_MAX
	};

	//All defined picture types
	enum PictureType
	{
		PICTURE_SPLASHART,
		PICTURE_STARTLOGO,
		PICTURE_CAR_01_TOP,
		PICTURE_CAR_02_TOP,
		PICTURE_CAR_03_TOP,
		PICTURE_CAR_04_TOP,
		PICTURE_CAR_05_TOP,
		PICTURE_MAX
	};

	//All defined animation types
	enum AnimationType
	{
		ANIMATION_EXPLOSION,
		ANIMATION_MAX
	};

	//All defined rocket types
	enum RocketType
	{
		ROCKET_01,
		ROCKET_MAX
	};

	//All defined HUD types
	enum HUDType
	{
		HUD_01,
		HUD_MAX
	};

	//All defined music types
	enum MusicType
	{
		MUSIC_START,
		MUSIC_MENU,
		MUSIC_OPTIONS,
		MUSIC_RADIO01,
		MUSIC_MAX
	};
}

#endif /* GAME_GAMEASSETS_H_ */

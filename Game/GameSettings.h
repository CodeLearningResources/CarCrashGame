/*
 * GameSettings.h
 *
 *  Created on: 20-jun.-2015
 *      Author: Thomas
 */

#ifndef GAME_GAMESETTINGS_H_
#define GAME_GAMESETTINGS_H_

#include <stdio.h>

#include "KeyboardKey.h"
#include "Player.h"

namespace CCG
{
	/*
	 * Class for storing all customizable game settings
	 */
	class GameSettings
	{
		public:
			/*
			 * Default constructor
			 */
			GameSettings(void);

			/*
			 * Constructor
			 * @param musicVolume Volume of the in-game music
			 * @param SFXVolume Volume of the in-game sound-effects
			 * @param FPSCap Frame Per Seconds Cap, 0 will turn the cap off
			 * @param VSync Activate/deactive VSync
			 * @param controlsPlayer01 Controls for player 1 (thisPlayer)
			 */
			GameSettings(int musicVolume, int SFXVolume, int FPSCap, bool VSync, KeyboardKey** controlsPlayer01);

			/*
			 * Copy constructor
			 */
			GameSettings(const GameSettings& settings);
			virtual ~GameSettings(void);

			//Get functions
			int getMusicVolume(void);
			int getSFXVolume(void);
			int getFPSCap(void);
			bool getVSyncActive(void);
			KeyboardKey** getControlsPlayer(int player);

			//Set functions
			void setMusicVolume(int volume);
			void setSFXVolume(int volume);
			void setFPSCap(int cap);
			void setVSync(bool flag);
			void setControlsPlayer(KeyboardKey** controls, int player);

		private:
			int musicVolume;
			int SFXVolume;
			int FPSCap;
			bool VSync;
			KeyboardKey** controlsPlayer01;
	};
}

#endif /* GAME_GAMESETTINGS_H_ */

/*
 * GameConfigParser.h
 *
 *  Created on: 20-jun.-2015
 *      Author: Thomas
 */

#ifndef GAME_GAMECONFIGMANAGER_H_
#define GAME_GAMECONFIGMANAGER_H_

#include <stdio.h>
#include <stdlib.h>

#include "GameSettings.h"
#include "XMLFileReader.h"
#include "XMLFileWriter.h"
#include "XMLNode.h"

namespace CCG
{
	/*
	 * Configuration manager to load and save the current settings (game + controls) of the
	 * game to a configuration XML file
	 */
	class GameConfigManager
	{
		public:
			/**
			 * constructor
			 */
			GameConfigManager(void);
			virtual ~GameConfigManager(void);

			/*
			 * Load the configuration from a XML file
			 * @param fileLocation The location of the configuration file
			 * @return 0 if succeeded, -1 if file could not be opened, -2 if file could not be interpreted (corrupted file)
			 */
			int loadConfig(const char* fileLocation);

			/*
			 * Save the configuration to a XML file
			 * @param fileLocation The location for the configuration file
			 * @see setSettings()
			 * @return 0 if succeeded, -1 if file could not be made, -2 if settings are not set in the manager
			 */
			int saveConfig(const char* fileLocation);

			/*
			 * Get the current loaded settings
			 * @return The current loaded settings, NULL if no settings are loaded
			 */
			GameSettings* getSettings(void);

			/*
			 * Set a new settings configuration
			 * @param settings The new settings to be loaded for storage
			 */
			void setSettings(GameSettings* settings);

		private:
			GameSettings* settings;		//Loaded settings
	};
}

#endif /* GAME_GAMECONFIGMANAGER_H_ */

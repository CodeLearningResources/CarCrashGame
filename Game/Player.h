/*
 * Player.h
 *
 *  Created on: 4-apr.-2015
 *      Author: Thomas
 */

#ifndef GAME_PLAYER_H_
#define GAME_PLAYER_H_

#include <stdio.h>
#include <string>

#include "../GameElements/Car.h"
#include "KeyboardKey.h"
#include "Event.h"

namespace CCG
{
	//Game controls
	enum PlayerControls
	{
		PLAYER_CONTROL_UP,
		PLAYER_CONTROL_RIGHT,
		PLAYER_CONTROL_DOWN,
		PLAYER_CONTROL_LEFT,
		//PLAYER_CONTROL_NITRO,
		PLAYER_CONTROL_ROCKET,
		PLAYER_CONTROL_MAX
	};

	class Player
	{
		public:
			/*
			 * Default constructor
			 */
			Player(void);

			/*
			 * Constructor
			 * @param name The name of the player
			 * @param controlMacro Set controls by one of the predefined macro's
			 */
			Player(std::string name, int controlMacro);

			/*
			 * Destructor
			 */
			virtual ~Player(void);

			/*
			 * Set the controls by one of the predefined macro's
			 * @param macro Selected macro
			 */
			void initializeControls(int macro);

			/*
			 * Handle the events for controlling the player car
			 * @param event Keyboard event
			 */
			void handleEvent(Event* event);

			/*
			 * Get the selected controls for the player
			 * @return array with the bounded keys for each control
			 */
			KeyboardKey** getControls(void);

			/*
			 * Set the controls for the player
			 * @param controls Array with the bounded keys for each control
			 */
			void setControls(KeyboardKey** controls);

			/*
			 * Set the name of the player
			 */
			void setName(std::string name);

			/*
			 * Set the score of the player
			 */
			void setScore(float points);

			/*
			 * Assign a car to the player
			 */
			void setCar(Car* playerCar);

			/*
			 * Set the health of the player car
			 */
			void setHealth(int points);

			/*
			 * Set the nitro value of the player car
			 */
			void setNitro(int points);

			/*
			 * Set the amount of rockets for the player
			 */
			void setRockets(int rockets);

			/*
			 * Set the state of the player for firing a rocket
			 */
			void setFiring(bool flag);

			//Get methods
			std::string getName(void);
			float getScore(void);
			Car* getPlayerCar(void);
			int getHealth(void);
			int getNitro(void);
			int getRockets(void);

			bool isAlive(void);
			bool isFiring(void);

			/*
			 * Add points to the score of the player
			 */
			void addScore(float points);

			/*
			 * Add rockets to the stock of the player
			 */
			void addRockets(int rockets);

		private:
			std::string name;
			float score;
			int rockets;
			bool fireRocket;
			bool rocketFired;
			Car* playerCar;
			KeyboardKey** controls;
	};
}

#endif /* GAME_PLAYER_H_ */

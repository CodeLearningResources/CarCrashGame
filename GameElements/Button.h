/*
 * Button.h
 *
 *  Created on: 15-apr.-2015
 *      Author: Thomas
 */

#ifndef GAME_BUTTON_H_
#define GAME_BUTTON_H_

#include "GameElement.h"

namespace CCG
{
	enum GameButtonState
	{
		GAMEBUTTON_NORMAL,
		GAMEBUTTON_PRESSED,
		GAMEBUTTON_HIGHLIGHTED,
		GAMEBUTTON_INACTIVE,
		GAMEBUTTON_MAX
	};

	/*
	 * Abstract game element class for buttons
	 */
	class Button : public GameElement
	{
		public:
			~Button(void);

			/*
			 * Set the button clickable or not
			 */
			void setInactive(bool flag);
			void setButtonState(GameButtonState state);

			/*
			 * Get if the button is clickable or not
			 */
			bool getInactiveState(void) const;
			GameButtonState getButtonState(void) const;

			/*
			 * Change the state of the button according to the cursor input
			 * @param posX The X-position of the cursor
			 * @param posY The Y-position of the cursor
			 * @param pressed The state if the cursor is pressed
			 * @return The result if the button has been activated/clicked by the cursor
			 */
			bool checkButtonState(int posX, int posY, bool pressed);

			virtual void playClickSound(void) = 0;

		private:
			bool inactive;
			GameButtonState state;

		protected:
			Button(void);
			Button(const Button& button);
	};
}

#endif /* GAME_BUTTON_H_ */

/*
 * Messagebox.h
 *
 *  Created on: 16-jun.-2015
 *      Author: Thomas
 */

#ifndef GAMEELEMENTS_MESSAGEBOX_H_
#define GAMEELEMENTS_MESSAGEBOX_H_

#include <string>

#include "GameElement.h"

namespace CCG
{
	/*
	 * Abstract game element class for messageboxes
	 */
	class Messagebox : public GameElement
	{
		public:
			~Messagebox(void);

			virtual void setMessageText(std::string* text);

			/*
			 * Set the texts of the buttons
			 * @param buttonText1 Set the button with the given text, when NULL the button will not be displayed
			 * @param buttonText2 Set the button with the given text if buttonText1 is not NULL, when NULL the button will not be displayed
			 */
			virtual void setButtons(std::string* buttonText1, std::string* buttonText2);

			std::string* getMessageText(void);
			std::string* getButtonText1(void);
			std::string* getButtonText2(void);

			/*
			 * Get the state if a button is pressed
			 * @return Returns the index of the pressed button or -1 if no button is pressed
			 */
			virtual int checkMessageboxState(int posX, int posY, bool pressed) = 0;

		private:
			std::string messageText;
			std::string buttonText1;
			std::string buttonText2;

		protected:
			Messagebox(void);
			Messagebox(std::string* messageText, std::string* buttonText1, std::string* buttonText2);
			int displayedButtons;
	};
}

#endif /* GAMEELEMENTS_MESSAGEBOX_H_ */

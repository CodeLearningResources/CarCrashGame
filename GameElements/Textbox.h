/*
 * Textbox.h
 *
 *  Created on: 17-apr.-2015
 *      Author: Thomas
 */

#ifndef GAMEELEMENTS_TEXTBOX_H_
#define GAMEELEMENTS_TEXTBOX_H_

#include <string>

#include "GameElement.h"

namespace CCG
{
	enum TextboxState
	{
		TEXTBOX_STATE_NORMAL,
		TEXTBOX_STATE_ACTIVE,
		TEXTBOX_STATE_HIGHLIGHTED,
		TEXTBOX_STATE_MAX
	};

	/*
	 * Abstract game element class for textboxes
	 */
	class Textbox : public GameElement
	{
		public:
			~Textbox(void);

			void setCharactersLimit(int limit);				//Maximum allowed characters in the box
			void setFocus(bool flag);
			virtual void setText(std::string* text);

			int getCharactersLimit(void) const;
			std::string getText(void) const;
			TextboxState getTextboxState(void) const;

			void checkFocusState(int posX, int posY, bool selected);

			virtual void addCharacter(char character);
			virtual void delCharacter(void);

		private:
			int limit;
			std::string text;
			TextboxState state;

		protected:
			Textbox(void);
			Textbox(const Textbox& textbox);
	};
}

#endif /* GAMEELEMENTS_TEXTBOX_H_ */

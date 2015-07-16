/*
 * Checkbox.h
 *
 *  Created on: 10-mei-2015
 *      Author: Thomas
 */

#ifndef GAMEELEMENTS_CHECKBOX_H_
#define GAMEELEMENTS_CHECKBOX_H_

#include "GameElement.h"

namespace CCG
{
	enum GameCheckboxState
	{
		GAMECHECKBOX_NORMAL,
		GAMECHECKBOX_HIGHLIGHTED,
		GAMECHECKBOX_MAX
	};

	/*
	 * Abstract game element class for checkboxes
	 */
	class Checkbox : public GameElement
	{
		public:
			~Checkbox(void);

			void setChecked(bool checked);
			void setInactive(bool flag);

			bool getCheckState(void) const;
			bool getInactiveState(void) const;
			GameCheckboxState getCheckboxState(void) const;

			bool checkCheckboxState(int posX, int posY, bool pressed);

		private:
			bool inactive;
			bool checked;
			GameCheckboxState state;

		protected:
			Checkbox(void);
			Checkbox(bool checked);
			Checkbox(const Checkbox& checkbox);
	};
}

#endif /* GAMEELEMENTS_CHECKBOX_H_ */

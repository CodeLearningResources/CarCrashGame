/*
 * Cursor.h
 *
 *  Created on: 19-jun.-2015
 *      Author: Thomas
 */

#ifndef GAMEELEMENTS_CURSOR_H_
#define GAMEELEMENTS_CURSOR_H_

#include "GameElement.h"

namespace CCG
{
	enum CursorState
	{
		CURSOR_STATE_NORMAL,
		CURSOR_STATE_CLICK,
		CURSOR_STATE_MAX
	};

	/*
	 * Abstract game element class for cursors
	 */
	class Cursor : public GameElement
	{
		public:
			~Cursor(void);

			void setCursorPosition(int posX, int posY, bool clicking);

			CursorState getCursorState(void);

		private:
			CursorState state;

		protected:
			Cursor(void);
			Cursor(const Cursor& cursor);
	};
}

#endif /* GAMEELEMENTS_CURSOR_H_ */

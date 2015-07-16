/*
 * Background.h
 *
 *  Created on: 22-mrt.-2015
 *      Author: Thomas
 */

#ifndef GAMEELEMENTS_BACKGROUND_H_
#define GAMEELEMENTS_BACKGROUND_H_

#include "GameElement.h"

namespace CCG
{
	enum ScrollDirection
	{
		SCROLL_OFF,
		SCROLL_HORIZONTAL,
		SCROLL_VERTICAL,
		SCROLL_DIAGONAL_FIRST,
		SCROLL_DIAGONAL_SECOND
	};

	/*
	 * Abstract game element class for backgrounds
	 */
	class Background : public GameElement
	{
		public:
			~Background(void);

			void setSpeed(float speed);

			ScrollDirection getScrollDirection(void) const;
			float getSpeed(void) const;

			void move(float timeStep);	//Override of move method

		private:
			ScrollDirection direction;

		protected:
			Background(void);
			Background(ScrollDirection direction);
			Background(const Background& background);
	};
}

#endif /* GAMEELEMENTS_BACKGROUND_H_ */

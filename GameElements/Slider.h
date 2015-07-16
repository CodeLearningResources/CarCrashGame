/*
 * Slider.h
 *
 *  Created on: 27-apr.-2015
 *      Author: Thomas
 */

#ifndef GAMEELEMENTS_SLIDER_H_
#define GAMEELEMENTS_SLIDER_H_

#include "GameElement.h"

namespace CCG
{
	/*
	 * Abstract game element class for sliders
	 */
	class Slider : public GameElement
	{
		public:
			~Slider(void);

			void setValue(int value);
			void setInactive(bool flag);

			int getValue(void) const;
			bool getInactiveState(void) const;

			bool checkSliderState(int posX, int posY, bool pressed);

		private:
			bool inactive;
			int value;

		protected:
			Slider(void);
			Slider(int value);
			Slider(const Slider& slider);
	};
}

#endif /* GAMEELEMENTS_SLIDER_H_ */

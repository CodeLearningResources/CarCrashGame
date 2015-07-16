/*
 * Text.h
 *
 *  Created on: 23-mrt.-2015
 *      Author: Thomas
 */

#ifndef GAMEELEMENTS_TEXT_H_
#define GAMEELEMENTS_TEXT_H_

#include <string>

#include "GameElement.h"

namespace CCG
{
	/*
	 * Abstract game element class for texts
	 */
	class Text : public GameElement
	{
		public:
			~Text(void);

			virtual void setText(std::string text);

			virtual void setWrapLength(uint32_t wrapLength);
			virtual void setColor(uint8_t red, uint8_t green, uint8_t blue, uint8_t opaque);

			std::string getText(void) const;
			uint32_t getWrapLength(void) const;
			uint8_t getRed(void) const;
			uint8_t getGreen(void) const;
			uint8_t getBlue(void) const;
			uint8_t getOpaque(void) const;

		private:
			std::string text;
			uint32_t wrapLength;	//Max length in pixels until newline is used (0: no wrapping)
			uint8_t red;			//RGB: red-value: 0-255
			uint8_t green;			//RGB: green-value: 0-255
			uint8_t blue;			//RGB: blue-value: 0-255
			uint8_t opaque;			//Opacity: 0-255

		protected:
			Text(void);
			Text(std::string text);
			Text(const Text& text);
	};
}

#endif /* GAMEELEMENTS_TEXT_H_ */

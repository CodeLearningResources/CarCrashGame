/*
 * Picture.h
 *
 *  Created on: 16-apr.-2015
 *      Author: Thomas
 */

#ifndef GAMEELEMENTS_PICTURE_H_
#define GAMEELEMENTS_PICTURE_H_

#include "GameElement.h"

namespace CCG
{
	/*
	 * Abstract game element class for pictures
	 */
	class Picture : public GameElement
	{
		public:
			~Picture(void);

		protected:
			Picture(void);
			Picture(const Picture& picture);
	};
}

#endif /* GAMEELEMENTS_PICTURE_H_ */

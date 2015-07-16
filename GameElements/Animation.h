/*
 * Animation.h
 *
 *  Created on: 7-jun.-2015
 *      Author: Thomas
 */

#ifndef GAMEELEMENTS_ANIMATION_H_
#define GAMEELEMENTS_ANIMATION_H_

#include "GameElement.h"

namespace CCG
{
	/*
	 * Abstract game element class for animations
	 */
	class Animation : public GameElement
	{
		public:
			~Animation(void);

			virtual void setAnimationCurrentFrame(int frame) = 0;
			virtual void setAnimationRepeat(bool flag) = 0;

			virtual bool isRunning(void) const = 0;

			virtual void run(void) = 0;
			virtual void stop(void) = 0;

			virtual void updateAnimation(float timeStep) = 0;

		protected:
			Animation(void);
			Animation(const Animation& animation);
	};
}

#endif /* GAMEELEMENTS_ANIMATION_H_ */

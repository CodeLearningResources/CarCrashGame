/*
 * GameElement.h
 *
 *  Created on: 15-mrt.-2015
 *      Author: Thomas
 */

#ifndef GAMEELEMENTS_GAMEELEMENT_H_
#define GAMEELEMENTS_GAMEELEMENT_H_

#include <stdio.h>
#include <cmath>

namespace CCG
{
	enum Direction
	{
		DIRECTION_UP,
		DIRECTION_RIGHT,
		DIRECTION_DOWN,
		DIRECTION_LEFT
	};

	/*
	 * Abstract class for all game elements
	 */
	class GameElement
	{
		public:
			virtual ~GameElement();
			void setSize(float sizeX, float sizeY);
			void setPos(float posX, float posY);
			void setCollider(float posX, float posY, float sizeX, float sizeY);		//Collider box used by collision detection
			void setVelocity(float velX, float velY);
			void setRotation(float rotation);
			void setRelRotation(float rotation);
			void setRotVelocity(float velRot);
			void setPosX(float posX);
			void setPosY(float posY);
			void setVelX(float velX);
			void setVelY(float velY);
			float getSizeX(void) const;
			float getSizeY(void) const;
			float getPosX(void) const;
			float getPosY(void) const;
			float getVelX(void) const;
			float getVelY(void) const;
			float getColliderPosX(void) const;
			float getColliderPosY(void) const;
			float getColliderSizeX(void) const;
			float getColliderSizeY(void) const;
			float getRotation(void) const;
			float getRelRotation(void) const;
			float getRotVelocity(void) const;

			bool checkInBoundaries(int x, int y, int width, int height);			//Check if object is between the given boundaries
			virtual bool checkCollision(GameElement* object);
			virtual bool checkIntersection(int posX, int posY);						//Check if object intersect with the given point
			virtual void move(float timeStep);

			virtual void visible(bool flag) = 0;
			virtual bool isVisible(void) = 0;
			virtual void update(void) = 0;

		private:
			float posX, posY;
			float sizeX, sizeY;
			float colliderPosX, colliderPosY;
			float colliderSizeX, colliderSizeY;
			float velX, velY;		//Translation in pixels per seconds
			float rotation;
			float relRotation;
			float velRot;

		protected:
			GameElement();
			GameElement(const GameElement& gameElement);
	};
}

#endif /* GAMEELEMENTS_GAMEELEMENT_H_ */

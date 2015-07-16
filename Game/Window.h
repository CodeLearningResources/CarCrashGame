/*
 * Window.h
 *
 *  Created on: 23-mrt.-2015
 *      Author: Thomas
 */

#ifndef GAME_WINDOW_H_
#define GAME_WINDOW_H_

/*
 * Abstract window class
 */
namespace CCG
{
	class Window
	{
		public:
			virtual ~Window(void);

			virtual int showWindow(void) = 0;
			virtual int hideWindow(void) = 0;
			virtual int updateWindow(void) = 0;

			virtual void setTitle(const char* title) = 0;
			virtual void setSize(int width, int height) = 0;
			virtual void setFPSCap(int cap) = 0;
			virtual int setHardwareAcceleration(bool flag) = 0;
			virtual int setVSync(bool flag) = 0;

			virtual int getFPSCap(void) const = 0;
			virtual bool getHardwareAcceleration(void) const = 0;
			virtual bool getVSync(void) const = 0;

		protected:
			Window(void);
	};
}

#endif /* GAME_WINDOW_H_ */

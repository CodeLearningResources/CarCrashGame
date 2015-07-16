/*
 * KeyboardKey.h
 *
 *  Created on: 13-jun.-2015
 *      Author: Thomas
 */

#ifndef GAME_KEYBOARDKEY_H_
#define GAME_KEYBOARDKEY_H_

#include <string>
#include <stdio.h>

#include "KeyboardKey.h"

namespace CCG
{
	//Key definitions
	enum KeyboardValue
	{
		KEY_UNDEFINED = -1,
		KEY_BACKSPACE = 8,		//8
		KEY_TAB,				//9
		KEY_ENTER,				//13
		//KEY_CLEAR,
		//KEY_RETURN,
		//KEY_PAUSE,
		KEY_ESCAPE = 27,		//27
		KEY_SPACE = 32,			//32
		//KEY_EXCLAIM,
		//KEY_DUBBLEQUOTE,
		//KEY_HASH,
		//KEY_DOLLAR,
		//KEY_AMPERSAND,
		//KEY_QUOTE,
		//KEY_LEFTPARENTHES,
		//KEY_RIGHTPARENTHES,
		//KEY_ASTERISK,
		//KEY_PLUS,
		//KEY_COMMA,
		//KEY_MINUS,
		//KEY_PERIOD,
		//KEY_SLASH,
		KEY_0 = 48,				//48
		KEY_1,					//49
		KEY_2,					//50
		KEY_3,					//51
		KEY_4,					//52
		KEY_5,					//53
		KEY_6,					//54
		KEY_7,					//55
		KEY_8,					//56
		KEY_9,					//57
		//KEY_COLON,
		//KEY_SEMICOLON,
		//KEY_LESS,
		//KEY_EQUALS,
		//KEY_GREATER,
		//KEY_QUESTION,
		//KEY_AT,
		//KEY_LEFTBRACKET,
		//KEY_BACKSLASH,
		//KEY_RIGHTBRACKET,
		//KEY_CARET,
		//KEY_UNDERSCORE,
		//KEY_BACKQUOTE,
		KEY_A = 65,				//65
		KEY_B,					//66
		KEY_C,					//67
		KEY_D,					//68
		KEY_E,					//69
		KEY_F,					//70
		KEY_G,					//71
		KEY_H,					//72
		KEY_I,					//73
		KEY_J,					//74
		KEY_K,					//75
		KEY_L,					//76
		KEY_M,					//77
		KEY_N,					//78
		KEY_O,					//79
		KEY_P,					//80
		KEY_Q,					//81
		KEY_R,					//82
		KEY_S,					//83
		KEY_T,					//84
		KEY_U,					//85
		KEY_V,					//86
		KEY_W,					//87
		KEY_X,					//88
		KEY_Y,					//89
		KEY_Z,					//90
		KEY_DELETE = 46,		//46
		KEY_KEYPAD0 = 96,		//96
		KEY_KEYPAD1,			//97
		KEY_KEYPAD2,			//98
		KEY_KEYPAD3,			//99
		KEY_KEYPAD4,			//100
		KEY_KEYPAD5,			//101
		KEY_KEYPAD6,			//102
		KEY_KEYPAD7,			//103
		KEY_KEYPAD8,			//104
		KEY_KEYPAD9,			//105
		KEY_KEYPADPERIOD = 110,	//110
		KEY_KEYPADDIVIDE,		//111
		KEY_KEYPADMULTIPLY = 106,	//106
		KEY_KEYPADMINUS = 109,	//109
		KEY_KEYPADPLUS = 107,	//107
		KEY_KEYPADENTER = 13,	//13
		//KEY_KEYPADEQUALS,
		KEY_LEFT = 37,			//37
		KEY_UP,					//38
		KEY_RIGHT,				//39
		KEY_DOWN,				//40
		KEY_INSERT = 45,		//45
		KEY_PAGEUP = 33,		//33
		KEY_PAGEDOWN,			//34
		KEY_END,				//35
		KEY_HOME,				//36
		KEY_F1 = 112,			//112
		KEY_F2,					//113
		KEY_F3,					//114
		KEY_F4,					//115
		KEY_F5,					//116
		KEY_F6,					//117
		KEY_F7,					//118
		KEY_F8,					//119
		KEY_F9,					//120
		KEY_F10,				//121
		KEY_F11,				//122
		KEY_F12,				//123
		//KEY_NUMLOCK,
		//KEY_CAPSLOCK,
		//KEY_SCROLLLOCK,
		//KEY_RIGHTSHIFT,
		//KEY_LEFTSHIFT,
		//KEY_RIGHTCONTROL,
		//KEY_LEFTCONTROL,
		//KEY_RIGHTALT,
		//KEY_LEFTALT,
		//KEY_RIGHTMETA,
		//KEY_LEFTMETA,
		//KEY_LEFTSUPER,		//Left windows key
		//KEY_RIGHTSUPER,		//Right windows key
		//KEY_MODE,
		//KEY_HELP,
		//KEY_PRINT,
		//KEY_SYSREQ,
		//KEY_BREAK,
		//KEY_MENU,
		//KEY_POWER,
		//KEY_EURO
	};

	/*
	 * Class for defining a keyboard key
	 */
	class KeyboardKey
	{
		public:
			/*
			 * Default constructor
			 */
			KeyboardKey(void);

			/*
			 * Constructor
			 * @param value The key value
			 */
			KeyboardKey(KeyboardValue value);

			/*
			 * Copy constructor
			 */
			KeyboardKey(const KeyboardKey& keyboardKey);

			/*
			 * Destructor
			 */
			virtual ~KeyboardKey(void);

			//Get functions
			KeyboardValue getKeyValue(void) const;

			/*
			 * Get the string value of the defined key
			 * @return String value of the key
			 */
			std::string getString(void) const;

			//Set functions
			void setKeyValue(KeyboardValue value);

		private:
			KeyboardValue keyValue;
	};
}

#endif /* GAME_KEYBOARDKEY_H_ */

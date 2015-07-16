/*
 * KeyboardKey.cpp
 *
 *  Created on: 13-jun.-2015
 *      Author: Thomas
 */

#include "KeyboardKey.h"

using namespace CCG;

KeyboardKey::KeyboardKey()
{
	keyValue = KEY_UNDEFINED;
}

KeyboardKey::KeyboardKey(KeyboardValue value)
{
	this->keyValue = value;
}

KeyboardKey::KeyboardKey(const KeyboardKey& keyboardKey)
{
	this->keyValue = keyboardKey.keyValue;
}

KeyboardKey::~KeyboardKey()
{

}

KeyboardValue KeyboardKey::getKeyValue() const
{
	return this->keyValue;
}

std::string KeyboardKey::getString() const
{
	int charValue;
	char* tempValue = new char[10]();
	std::string stringValue;

	if(this->keyValue >= KEY_0 && this->keyValue <= KEY_9)						//Numeric key
	{
		charValue = (int)'0' + (this->keyValue - KEY_0);
		stringValue = (char)charValue;
	}
	else if(this->keyValue >= KEY_A && this->keyValue <= KEY_Z)					//Alphabetic key
	{
		charValue = (int)'A' + (this->keyValue - KEY_A);
		stringValue = (char)charValue;
	}
	else if(this->keyValue >= KEY_KEYPAD0 && this->keyValue <= KEY_KEYPAD9)		//Numeric-keypad key
	{
		charValue = this->keyValue - KEY_KEYPAD0;
		sprintf(tempValue, "Keypad-%d", charValue);
		stringValue = tempValue;
	}
	else if(this->keyValue >= KEY_F1 && this->keyValue <= KEY_F12)				//Function key
	{
		charValue = this->keyValue - KEY_F1 + 1;
		sprintf(tempValue, "F%d", charValue);
		stringValue = tempValue;
	}
	else
	{
		switch(this->keyValue)													//Special defined keys
		{
			case KEY_BACKSPACE:
				stringValue = "Backspace";
				break;
			case KEY_TAB:
				stringValue = "Tab";
				break;
			case KEY_ENTER:
				stringValue = "Enter";
				break;
			case KEY_ESCAPE:
				stringValue = "Escape";
				break;
			case KEY_SPACE:
				stringValue = "Spacebar";
				break;
			case KEY_DELETE:
				stringValue = "Delete";
				break;
			case KEY_KEYPADPERIOD:
				stringValue = "Keypad-point";
				break;
			case KEY_KEYPADDIVIDE:
				stringValue = "Keypad-divide";
				break;
			case KEY_KEYPADMULTIPLY:
				stringValue = "Keypad-multiply";
				break;
			case KEY_KEYPADMINUS:
				stringValue = "Keypad-minus";
				break;
			case KEY_KEYPADPLUS:
				stringValue = "Keypad-plus";
				break;
			case KEY_KEYPADENTER:
				stringValue = "Keypad-enter";
				break;
			case KEY_UP:
				stringValue = "Up-key";
				break;
			case KEY_RIGHT:
				stringValue = "Right-key";
				break;
			case KEY_DOWN:
				stringValue = "Down-key";
				break;
			case KEY_LEFT:
				stringValue = "Left-key";
				break;
			case KEY_INSERT:
				stringValue = "Insert";
				break;
			case KEY_PAGEUP:
				stringValue = "PageUp";
				break;
			case KEY_PAGEDOWN:
				stringValue = "PageDown";
				break;
			case KEY_END:
				stringValue = "End";
				break;
			case KEY_HOME:
				stringValue = "Home";
				break;
			default:
				stringValue = "Undefined";
				break;
		}
	}

	delete(tempValue);

	return stringValue;
}

void KeyboardKey::setKeyValue(KeyboardValue value)
{
	this->keyValue = value;
}

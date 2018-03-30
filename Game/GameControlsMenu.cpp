/*
 * GameControlsMenu.cpp
 *
 *  Created on: 10-jun.-2015
 *      Author: Thomas
 */

#include "GameControlsMenu.h"

using namespace CCG;

GameControlsMenu::GameControlsMenu() : GameState()
{
	//Wait for input from keyboard for selected control index, when different from -1
	getKeyForControl = -1;
}

GameControlsMenu::GameControlsMenu(GameFactory* factory, GameStateManager* stateManager, GameManager* gameManager, Background* background) : GameState(factory, stateManager, gameManager)
{
	this->background = background;

	//Wait for input from keyboard for selected control index, when different from -1
	this->getKeyForControl = -1;
}

GameControlsMenu::~GameControlsMenu()
{

}

void GameControlsMenu::initialize()
{
	frameTimer = factory->getTimer();
	factory->getCursor()->visible(true);
	getKeyForControl = -1;

	//Get control mapping of player
	controlMapping = new KeyboardKey*[PLAYER_CONTROL_MAX]();

	for(int i = 0; i < PLAYER_CONTROL_MAX; i++)
	{
		controlMapping[i] = new KeyboardKey(*gameManager->getThisPlayer()->getControls()[i]);
	}

	//Initialize options text
	optionsText = factory->getText("CONTROLS", FONT_TITLE_LARGE);
	optionsText->setPos(512 - optionsText->getSizeX()/2, 150 - optionsText->getSizeY()/2);
	optionsText->setColor(255, 255, 255, 0);
	optionsText->visible(true);

	//Initialize buttons for controls
	controlsButtons = new Button*[PLAYER_CONTROL_MAX];

	for(int i = 0; i < PLAYER_CONTROL_MAX; i++)
	{
		controlsButtons[i] = factory->getButton(BUTTON_01);
		controlsButtons[i]->setSize(185, 60);
		controlsButtons[i]->setPos(610 - controlsButtons[i]->getSizeX()/2, (70 * i) + 225 - controlsButtons[i]->getSizeY()/2);
		controlsButtons[i]->visible(true);
	}

	//Control buttons values
	controlsValueTexts = new Text*[PLAYER_CONTROL_MAX];

	for(int i = 0; i < PLAYER_CONTROL_MAX; i++)
	{
		controlsValueTexts[i] = factory->getText("VALUE", FONT_TITLE_NORMAL);
		controlsValueTexts[i]->setPos(610 - controlsValueTexts[i]->getSizeX()/2, (70 * i) + 225 - controlsValueTexts[i]->getSizeY()/2);
		controlsValueTexts[i]->setColor(255, 255, 255, 0);
		controlsValueTexts[i]->visible(true);
	}

	//Control buttons meaning
	controlsTexts = new Text*[PLAYER_CONTROL_MAX];

	controlsTexts[PLAYER_CONTROL_UP] = factory->getText("Up", FONT_TITLE_NORMAL);
	controlsTexts[PLAYER_CONTROL_RIGHT] = factory->getText("Right", FONT_TITLE_NORMAL);
	controlsTexts[PLAYER_CONTROL_DOWN] = factory->getText("Down", FONT_TITLE_NORMAL);
	controlsTexts[PLAYER_CONTROL_LEFT] = factory->getText("Left", FONT_TITLE_NORMAL);
	//controlsTexts[PLAYER_CONTROL_NITRO] = factory->getText("Nitro", FONT_TITLE_NORMAL);
	controlsTexts[PLAYER_CONTROL_ROCKET] = factory->getText("Rockets / Select", FONT_TITLE_NORMAL);

	for(int i = 0; i < PLAYER_CONTROL_MAX; i++)
	{
		controlsTexts[i]->setPos(310, (70 * i) + 225 - controlsTexts[i]->getSizeY()/2);
		controlsTexts[i]->setColor(255, 255, 255, 0);
		controlsTexts[i]->visible(true);
	}

	//Messagebox to indicate waiting for keyboard input to assign new key or information
	messagebox = factory->getMessagebox(MESSAGEBOX_01);
	messagebox->setSize(550, 275);
	messagebox->setPos(factory->getScreenWidth()/2 - messagebox->getSizeX()/2, factory->getScreenHeight()/2 - messagebox->getSizeY()/2);

	//Initialize buttons
	restoreButton = factory->getButton(BUTTON_01);
	restoreButton->setSize(185, 60);
	restoreButton->setPos(610 - restoreButton->getSizeX()/2, (70 * PLAYER_CONTROL_MAX) + 225 - restoreButton->getSizeY()/2);
	restoreButton->visible(true);

	restoreText = factory->getText("Restore", FONT_TITLE_NORMAL);
	restoreText->setPos(610 - restoreText->getSizeX()/2, (70 * PLAYER_CONTROL_MAX) + 225 - restoreText->getSizeY()/2);
	restoreText->setColor(255, 255, 255, 0);
	restoreText->visible(true);

	applyButton = factory->getButton(BUTTON_01);
	applyButton->setSize(250, 60);
	applyButton->setPos(382 - applyButton->getSizeX()/2, 675 - applyButton->getSizeY()/2);
	applyButton->visible(true);

	applyText = factory->getText("Apply", FONT_TITLE_NORMAL);
	applyText->setPos(382 - applyText->getSizeX()/2, 675 - applyText->getSizeY()/2);
	applyText->setColor(255, 255, 255, 0);
	applyText->visible(true);

	cancelButton = factory->getButton(BUTTON_01);
	cancelButton->setSize(250, 60);
	cancelButton->setPos(642 - cancelButton->getSizeX()/2, 675 - cancelButton->getSizeY()/2);
	cancelButton->visible(true);

	cancelText = factory->getText("Cancel", FONT_TITLE_NORMAL);
	cancelText->setPos(642 - cancelText->getSizeX()/2, 675 - cancelText->getSizeY()/2);
	cancelText->setColor(255, 255, 255, 0);
	cancelText->visible(true);

	updateValues();
}

void GameControlsMenu::release()
{
	delete(frameTimer);
	frameTimer = NULL;

	for(int i = 0; i < PLAYER_CONTROL_MAX; i++)
	{
		delete(controlsButtons[i]);
		delete(controlsTexts[i]);
		delete(controlsValueTexts[i]);
		delete(controlMapping[i]);

		controlsButtons[i] = NULL;
		controlsTexts[i] = NULL;
		controlsValueTexts[i] = NULL;
		controlMapping[i] = NULL;
	}

	delete(controlMapping);
	controlMapping = NULL;

	delete(controlsButtons);
	controlsButtons = NULL;

	delete(controlsTexts);
	controlsTexts = NULL;

	delete(controlsValueTexts);
	controlsValueTexts = NULL;

	delete(restoreButton);
	restoreButton = NULL;

	delete(applyButton);
	applyButton = NULL;

	delete(cancelButton);
	cancelButton = NULL;

	delete(messagebox);
	messagebox = NULL;

	delete(optionsText);
	optionsText = NULL;

	delete(restoreText);
	restoreText = NULL;

	delete(applyText);
	applyText = NULL;

	delete(cancelText);
	cancelText = NULL;
}

void GameControlsMenu::pause()
{
	this->frameTimer->pause();
}

void GameControlsMenu::resume()
{
	this->frameTimer->unpause();
}

void GameControlsMenu::handleEvents(Event* event)
{
	int mouseX, mouseY = 0;
	bool mousePressed = false;

	if(event != NULL)
	{
		switch(event->getType())
		{
			case GAME_QUIT:
				stateManager->exitGame();
				break;
			case KEYBOARD_EVENT:
				if(event->getKeyEvent()->getKeyValue() == KEY_ESCAPE && event->getButtonState() == BUTTON_PRESSED)
				{
					if(messagebox->isVisible())
					{
						//Close messagebox
						messagebox->visible(false);
					}
					else
					{
						//Exit controls menu
						stateManager->popState();
					}
				}

				if(getKeyForControl >= 0)
				{
					//Key binding to selected control
					if(event->getKeyEvent()->getKeyValue() == KEY_ESCAPE && event->getButtonState() == BUTTON_PRESSED)
					{
						//Cancel binding key to control
						getKeyForControl = -1;
					}
					else if(event->getButtonState() == BUTTON_PRESSED)
					{
						if(assignKeyToControl(event->getKeyEvent(), getKeyForControl) == 0)
						{
							updateValues();

							getKeyForControl = -1;

							messagebox->visible(false);
						}
					}
				}
				break;
			case MOUSE_EVENT:
				event->getMousePosition(&mouseX, &mouseY);

				if(event->getLMouseButtonState() == BUTTON_PRESSED)
				{
					mousePressed = true;
				}

				handleButtonsEvents(mouseX, mouseY, mousePressed);
				break;
			default:
				break;
		}
		delete(event);
		event = NULL;
	}
}

void GameControlsMenu::updateValues()
{
	for(int i = 0; i < PLAYER_CONTROL_MAX; i++)
	{
		controlsValueTexts[i]->setText(controlMapping[i]->getString());
		controlsValueTexts[i]->setPos(610 - controlsValueTexts[i]->getSizeX()/2, (70 * i) + 225 - controlsValueTexts[i]->getSizeY()/2);
	}
}

void GameControlsMenu::update()
{
	float timeStep = 0.0f;

	//Calculate time step
	if(!frameTimer->isPaused())
	{
		timeStep = frameTimer->getTicks() / 1000.f;
	}

	background->move(timeStep);
	background->update();

	optionsText->update();

	for(int i = 0; i < PLAYER_CONTROL_MAX; i++)
	{
		controlsButtons[i]->update();
		controlsValueTexts[i]->update();
		controlsTexts[i]->update();
	}

	restoreButton->update();
	restoreText->update();

	applyButton->update();
	applyText->update();

	cancelButton->update();
	cancelText->update();

	messagebox->update();

	if(!frameTimer->isPaused())
	{
		frameTimer->start();
	}
}

int GameControlsMenu::assignKeyToControl(KeyboardKey* key, int selectedControl)
{
	if(selectedControl >= 0 && selectedControl < PLAYER_CONTROL_MAX)
	{
		if(strcmp(key->getString().c_str(), "Undefined") == 0)
		{
			//Key is unknown, do not assign
			return -2;
		}
		else
		{
			controlMapping[selectedControl]->setKeyValue(key->getKeyValue());

			return 0;
		}
	}
	else
	{
		//Selected control doesn't exist
		return -1;
	}
}

bool GameControlsMenu::applySettings()
{
	int checkControl = 0;
	bool duplicateControl = false;

	//Check for duplicated assigned keys
	while(checkControl < (PLAYER_CONTROL_MAX - 1) && !duplicateControl)
	{
		for(int i = (checkControl + 1); i < PLAYER_CONTROL_MAX; i++)
		{
			if(controlMapping[checkControl]->getKeyValue() == controlMapping[i]->getKeyValue())
			{
				duplicateControl = true;
			}
		}

		checkControl++;
	}

	if(!duplicateControl)
	{
		gameManager->getThisPlayer()->setControls(this->controlMapping);

		return true;
	}
	else
	{
		return false;
	}
}

void GameControlsMenu::restoreSettings()
{
	for(int i = 0; i < PLAYER_CONTROL_MAX; i++)
	{
		controlMapping[i] = new KeyboardKey(*gameManager->getThisPlayer()->getControls()[i]);
	}

	updateValues();
}

void GameControlsMenu::handleButtonsEvents(int mouseX, int mouseY, bool mousePressed)
{
	if(!messagebox->isVisible())
	{
		//Check the set control buttons
		for(int i = 0; i < PLAYER_CONTROL_MAX; i++)
		{
			if(controlsButtons[i]->checkButtonState(mouseX, mouseY, mousePressed))
			{
				//Display messagebox
				std::string* messageText = new std::string("Press a key to set: '" + controlsTexts[i]->getText() + "'\nor press 'Esc' to cancel.");
				std::string* buttonText = new std::string("Cancel");

				messagebox->setMessageText(messageText);
				messagebox->setButtons(buttonText, NULL);
				messagebox->visible(true);

				//Wait for input from keyboard for selected control index, when different from -1
				getKeyForControl = i;

				controlsButtons[i]->playClickSound();

				delete(messageText);
				delete(buttonText);
			}
		}

		if(restoreButton->checkButtonState(mouseX, mouseY, mousePressed))
		{
			restoreButton->playClickSound();

			restoreSettings();
		}
		else if(applyButton->checkButtonState(mouseX, mouseY, mousePressed))
		{
			applyButton->playClickSound();

			if(applySettings())
			{
				stateManager->popState();
			}
			else
			{
				//Display messagebox
				std::string* messageText = new std::string("Not all controls are bounded to a separate keyboard key!");
				std::string* buttonText = new std::string("OK");

				messagebox->setMessageText(messageText);
				messagebox->setButtons(buttonText, NULL);
				messagebox->visible(true);

				delete(messageText);
				delete(buttonText);
			}
		}
		else if(cancelButton->checkButtonState(mouseX, mouseY, mousePressed))
		{
			cancelButton->playClickSound();

			stateManager->popState();
		}
	}
	else
	{
		if(messagebox->checkMessageboxState(mouseX, mouseY, mousePressed) > 0)
		{
			//Close messagebox
			//Cancel binding key to control
			getKeyForControl = -1;

			messagebox->visible(false);
		}
	}
}

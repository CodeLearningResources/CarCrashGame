/*
 * GameStartMenu.cpp
 *
 *  Created on: 12-apr.-2015
 *      Author: Thomas
 */

#include "GameStartMenu.h"

using namespace CCG;

GameStartMenu::GameStartMenu() : GameState()
{

}

GameStartMenu::GameStartMenu(GameFactory* factory, GameStateManager* stateManager, GameManager* gameManager) : GameState(factory, stateManager, gameManager)
{

}

GameStartMenu::~GameStartMenu()
{

}

void GameStartMenu::initialize()
{
	frameTimer = factory->getTimer();
	factory->getCursor()->visible(true);

	//Initialize music
	musicPlayer = factory->getMusicPlayer();
	musicPlayer->setMusic(factory->getMusic(MUSIC_START));
	musicPlayer->startMusic(true);

	//Initialize background
	background = factory->getBackground(BACKGROUND_MENU);
	background->setPos(0, 0);
	background->setSize(1071, 1071);
	background->setSpeed(25);
	background->visible(true);

	//Intialize messagebox
	messagebox = factory->getMessagebox(MESSAGEBOX_01);
	messagebox->setSize(550, 275);
	messagebox->setPos(factory->getScreenWidth()/2 - messagebox->getSizeX()/2, factory->getScreenHeight()/2 - messagebox->getSizeY()/2);

	//Initialize logo
	gameLogo = factory->getPicture(PICTURE_STARTLOGO);
	gameLogo->setSize(500, 407);
	gameLogo->setPos(512 - gameLogo->getSizeX()/2, 200 - gameLogo->getSizeY()/2);
	gameLogo->visible(true);

	//Initialize buttons
	singlePlayerButton = factory->getButton(BUTTON_01);
	singlePlayerButton->setSize(300, 60);
	singlePlayerButton->setPos(512 - singlePlayerButton->getSizeX()/2, 450 - singlePlayerButton->getSizeY()/2);
	singlePlayerButton->visible(true);

	singlePlayerText = factory->getText("Single Player", FONT_TITLE_NORMAL);
	singlePlayerText->setPos(512 - singlePlayerText->getSizeX()/2, 450 - singlePlayerText->getSizeY()/2);
	singlePlayerText->setColor(255, 255, 255, 0);
	singlePlayerText->visible(true);

	multiPlayerButton = factory->getButton(BUTTON_01);
	multiPlayerButton->setSize(300, 60);
	multiPlayerButton->setPos(512 - multiPlayerButton->getSizeX()/2, 520 - multiPlayerButton->getSizeY()/2);
	multiPlayerButton->setInactive(true);
	multiPlayerButton->visible(true);

	multiPlayerText = factory->getText("Multi Player", FONT_TITLE_NORMAL);
	multiPlayerText->setPos(512 - multiPlayerText->getSizeX()/2, 520 - multiPlayerText->getSizeY()/2);
	multiPlayerText->setColor(255, 255, 255, 0);
	multiPlayerText->visible(true);

	optionButton = factory->getButton(BUTTON_01);
	optionButton->setSize(300, 60);
	optionButton->setPos(512 - optionButton->getSizeX()/2, 590 - optionButton->getSizeY()/2);
	optionButton->visible(true);

	optionText = factory->getText("Options", FONT_TITLE_NORMAL);
	optionText->setPos(512 - optionText->getSizeX()/2, 590 - optionText->getSizeY()/2);
	optionText->setColor(255, 255, 255, 0);
	optionText->visible(true);

	exitButton = factory->getButton(BUTTON_01);
	exitButton->setSize(300, 60);
	exitButton->setPos(512 - exitButton->getSizeX()/2, 660 - exitButton->getSizeY()/2);
	exitButton->visible(true);

	exitText = factory->getText("Exit", FONT_TITLE_NORMAL);
	exitText->setPos(512 - exitText->getSizeX()/2, 660 - exitText->getSizeY()/2);
	exitText->setColor(255, 255, 255, 0);
	exitText->visible(true);
}

void GameStartMenu::release()
{
	delete(frameTimer);
	frameTimer = NULL;

	delete(background);
	background = NULL;

	delete(gameLogo);
	gameLogo = NULL;

	delete(messagebox);
	messagebox = NULL;

	delete(singlePlayerButton);
	singlePlayerButton = NULL;

	delete(multiPlayerButton);
	multiPlayerButton = NULL;

	delete(optionButton);
	optionButton = NULL;

	delete(exitButton);
	exitButton = NULL;

	delete(singlePlayerText);
	singlePlayerText = NULL;

	delete(multiPlayerText);
	multiPlayerText = NULL;

	delete(optionText);
	optionText = NULL;

	delete(exitText);
	exitText = NULL;
}

void GameStartMenu::pause()
{
	this->frameTimer->pause();
}

void GameStartMenu::resume()
{
	this->frameTimer->unpause();
}

void GameStartMenu::handleEvents(Event* event)
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
						messagebox->visible(false);
					}
					else
					{
						//Create messagebox
						std::string* exitMessage = new std::string("Are you sure you want to exit?");
						std::string* answerPositive = new std::string("Yes");
						std::string* answerNegative = new std::string("No");

						messagebox->setMessageText(exitMessage);
						messagebox->setButtons(answerPositive, answerNegative);
						messagebox->visible(true);

						delete(exitMessage);
						delete(answerPositive);
						delete(answerNegative);
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

void GameStartMenu::update()
{
	float timeStep = 0.0f;

	//Calculate time step
	if(!frameTimer->isPaused())
	{
		timeStep = frameTimer->getTicks() / 1000.f;
	}

	background->move(timeStep);
	background->update();

	gameLogo->update();

	singlePlayerButton->update();
	singlePlayerText->update();

	multiPlayerButton->update();
	multiPlayerText->update();

	optionButton->update();
	optionText->update();

	exitButton->update();
	exitText->update();

	messagebox->update();

	if(!frameTimer->isPaused())
	{
		frameTimer->start();
	}
}

void GameStartMenu::handleButtonsEvents(int mouseX, int mouseY, bool mousePressed)
{
	if(messagebox->isVisible())
	{
		//Exit game messagebox
		int buttonValue = messagebox->checkMessageboxState(mouseX, mouseY, mousePressed);

		if(buttonValue == 1)				//Button 1: positive answer
		{
			stateManager->exitGame();
		}
		else if(buttonValue == 2)			//Button 2: negative answer
		{
			messagebox->visible(false);
		}
	}
	else
	{
		if(singlePlayerButton->checkButtonState(mouseX, mouseY, mousePressed))
		{
			singlePlayerButton->playClickSound();
			stateManager->pushState(new GameSinglePlayerMenu(factory, stateManager, gameManager, background));
		}
		else if(multiPlayerButton->checkButtonState(mouseX, mouseY, mousePressed))
		{
			multiPlayerButton->playClickSound();
		}
		else if(optionButton->checkButtonState(mouseX, mouseY, mousePressed))
		{
			optionButton->playClickSound();
			stateManager->pushState(new GameOptionsMenu(factory, stateManager, gameManager, background));
		}
		else if(exitButton->checkButtonState(mouseX, mouseY, mousePressed))
		{
			exitButton->playClickSound();

			//Create messagebox
			std::string* exitMessage = new std::string("Are you sure you want to exit?");
			std::string* answerPositive = new std::string("Yes");
			std::string* answerNegative = new std::string("No");

			messagebox->setMessageText(exitMessage);
			messagebox->setButtons(answerPositive, answerNegative);
			messagebox->visible(true);

			delete(exitMessage);
			delete(answerPositive);
			delete(answerNegative);
		}
	}
}

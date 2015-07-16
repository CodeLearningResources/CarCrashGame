/*
 * GamePauzeMenu.cpp
 *
 *  Created on: 24-apr.-2015
 *      Author: Thomas
 */

#include "GamePauseMenu.h"

using namespace CCG;

GamePauseMenu::GamePauseMenu() : GameState()
{

}

GamePauseMenu::GamePauseMenu(GameFactory* factory, GameStateManager* stateManager, GameManager* gameManager) : GameState(factory, stateManager, gameManager)
{

}

GamePauseMenu::~GamePauseMenu()
{

}

void GamePauseMenu::initialize()
{
	frameTimer = factory->getTimer();
	factory->getCursor()->visible(true);

	//Initialize background
	background = factory->getBackground(BACKGROUND_MENU);
	background->setPos(0, 0);
	background->setSize(1071, 1071);
	background->setSpeed(25);
	background->visible(true);

	//Initialize pause text
	pauseText = factory->getText("PAUSE", FONT_TITLE_LARGE);
	pauseText->setPos(512 - pauseText->getSizeX()/2, 250 - pauseText->getSizeY()/2);
	pauseText->setColor(255, 255, 255, 0);
	pauseText->visible(true);

	//Initialize buttons
	resumeButton = factory->getButton(BUTTON_01);
	resumeButton->setSize(300, 60);
	resumeButton->setPos(512 - resumeButton->getSizeX()/2, 520 - resumeButton->getSizeY()/2);
	resumeButton->visible(true);

	resumeText = factory->getText("Resume", FONT_TITLE_NORMAL);
	resumeText->setPos(512 - resumeText->getSizeX()/2, 520 - resumeText->getSizeY()/2);
	resumeText->setColor(255, 255, 255, 0);
	resumeText->visible(true);

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

	exitText = factory->getText("Back to menu", FONT_TITLE_NORMAL);
	exitText->setPos(512 - exitText->getSizeX()/2, 660 - exitText->getSizeY()/2);
	exitText->setColor(255, 255, 255, 0);
	exitText->visible(true);
}

void GamePauseMenu::release()
{
	delete(background);
	background = NULL;

	delete(frameTimer);
	frameTimer = NULL;

	delete(resumeButton);
	resumeButton = NULL;

	delete(optionButton);
	optionButton = NULL;

	delete(exitButton);
	exitButton = NULL;

	delete(pauseText);
	pauseText = NULL;

	delete(resumeText);
	resumeText = NULL;

	delete(optionText);
	optionText = NULL;

	delete(exitText);
	exitText = NULL;
}

void GamePauseMenu::pause()
{
	this->frameTimer->pause();
}

void GamePauseMenu::resume()
{
	this->frameTimer->unpause();
}

void GamePauseMenu::handleEvents(Event* event)
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
					stateManager->popState();
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

void GamePauseMenu::update()
{
	float timeStep = 0.0f;

	//Calculate time step
	if(!frameTimer->isPaused())
	{
		timeStep = frameTimer->getTicks() / 1000.f;
	}

	background->move(timeStep);
	background->update();

	pauseText->update();

	resumeButton->update();
	resumeText->update();

	optionButton->update();
	optionText->update();

	exitButton->update();
	exitText->update();

	if(!frameTimer->isPaused())
	{
		frameTimer->start();
	}
}

void GamePauseMenu::handleButtonsEvents(int mouseX, int mouseY, bool mousePressed)
{
	if(resumeButton->checkButtonState(mouseX, mouseY, mousePressed))
	{
		stateManager->popState();
	}
	else if(optionButton->checkButtonState(mouseX, mouseY, mousePressed))
	{
		optionButton->playClickSound();

		stateManager->pushState(new GameOptionsMenu(factory, stateManager, gameManager, background));
	}
	else if(exitButton->checkButtonState(mouseX, mouseY, mousePressed))
	{
		exitButton->playClickSound();

		stateManager->setState(new GameStartMenu(factory, stateManager, gameManager));
	}
}

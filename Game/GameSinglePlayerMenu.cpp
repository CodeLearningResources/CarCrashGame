/*
 * GameSinglePlayerMenu.cpp
 *
 *  Created on: 16-apr.-2015
 *      Author: Thomas
 */

#include "GameSinglePlayerMenu.h"

using namespace CCG;

GameSinglePlayerMenu::GameSinglePlayerMenu() : GameState()
{
	this->selectedLevel = 1;
	this->selectedCar = 1;
	this->playerName = "player";
}

GameSinglePlayerMenu::GameSinglePlayerMenu(GameFactory* factory, GameStateManager* stateManager, GameManager* gameManager, Background* background) : GameState(factory, stateManager, gameManager)
{
	this->background = background;

	this->selectedLevel = 1;
	this->selectedCar = 1;

	if(gameManager != NULL)
	{
		this->playerName = gameManager->getThisPlayer()->getName();
	}
	else
	{
		this->playerName = "player";
	}
}

GameSinglePlayerMenu::~GameSinglePlayerMenu()
{

}

void GameSinglePlayerMenu::initialize()
{
	frameTimer = factory->getTimer();
	factory->getCursor()->visible(true);

	//Initialize music player
	musicPlayer = factory->getMusicPlayer();
	musicPlayer->pushMusic(factory->getMusic(MUSIC_MENU));
	musicPlayer->startMusic(true);

	//Initialize title text
	singlePlayerText = factory->getText("SINGLE PLAYER", FONT_TITLE_LARGE);
	singlePlayerText->setPos(512 - singlePlayerText->getSizeX()/2, 50 - singlePlayerText->getSizeY()/2);
	singlePlayerText->setColor(255, 255, 255, 0);
	singlePlayerText->visible(true);

	//Initialize player name textbox
	playernameTextbox = factory->getTextbox(TEXTBOX_01);
	playernameTextbox->setSize(450, 60);
	playernameTextbox->setPos(512 - playernameTextbox->getSizeX()/2, 145 - playernameTextbox->getSizeY()/2);
	playernameTextbox->setText(&this->playerName);
	playernameTextbox->visible(true);

	//Initialize menu texts
	menuPlayernameText = factory->getText("Player name", FONT_TITLE_NORMAL);
	menuPlayernameText->setPos(50, 100 - menuPlayernameText->getSizeY()/2);
	menuPlayernameText->setColor(255, 255, 255, 0);
	menuPlayernameText->visible(true);

	menuLevelText = factory->getText("Level", FONT_TITLE_NORMAL);
	menuLevelText->setPos(50, 225 - menuLevelText->getSizeY()/2);
	menuLevelText->setColor(255, 255, 255, 0);
	menuLevelText->visible(true);

	menuCarText = factory->getText("Car", FONT_TITLE_NORMAL);
	menuCarText->setPos(50, 415 - menuCarText->getSizeY()/2);
	menuCarText->setColor(255, 255, 255, 0);
	menuCarText->visible(true);

	//Initialize buttons
	returnButton = factory->getButton(BUTTON_01);
	returnButton->setSize(150, 60);
	returnButton->setPos(90 - returnButton->getSizeX()/2, 720 - returnButton->getSizeY()/2);
	returnButton->visible(true);

	returnText = factory->getText("return", FONT_TITLE_NORMAL);
	returnText->setPos(90 - returnText->getSizeX()/2, 720 - returnText->getSizeY()/2);
	returnText->setColor(255, 255, 255, 0);
	returnText->visible(true);

	startButton = factory->getButton(BUTTON_01);
	startButton->setSize(300, 80);
	startButton->setPos(512 - startButton->getSizeX()/2, 710 - startButton->getSizeY()/2);
	startButton->visible(true);

	startText = factory->getText("START", FONT_TITLE_LARGE);
	startText->setPos(512 - startText->getSizeX()/2, 710 - startText->getSizeY()/2);
	startText->setColor(255, 255, 255, 0);
	startText->visible(true);

	nextLevelButton = factory->getButton(BUTTON_01);
	nextLevelButton->setSize(150, 60);
	nextLevelButton->setPos(592 - nextLevelButton->getSizeX()/2, 350 - nextLevelButton->getSizeY()/2);
	nextLevelButton->visible(true);

	nextLevelText = factory->getText("Next", FONT_TITLE_NORMAL);
	nextLevelText->setPos(592 - nextLevelText->getSizeX()/2, 350 - nextLevelText->getSizeY()/2);
	nextLevelText->setColor(255, 255, 255, 0);
	nextLevelText->visible(true);

	prevLevelButton = factory->getButton(BUTTON_01);
	prevLevelButton->setSize(150, 60);
	prevLevelButton->setPos(432 - prevLevelButton->getSizeX()/2, 350 - prevLevelButton->getSizeY()/2);
	prevLevelButton->visible(true);

	prevLevelText = factory->getText("Previous", FONT_TITLE_NORMAL);
	prevLevelText->setPos(432 - prevLevelText->getSizeX()/2, 350 - prevLevelText->getSizeY()/2);
	prevLevelText->setColor(255, 255, 255, 0);
	prevLevelText->visible(true);

	nextCarButton = factory->getButton(BUTTON_01);
	nextCarButton->setSize(150, 60);
	nextCarButton->setPos(712 - nextCarButton->getSizeX()/2, 550 - nextCarButton->getSizeY()/2);
	nextCarButton->visible(true);

	nextCarText = factory->getText("Next", FONT_TITLE_NORMAL);
	nextCarText->setPos(712 - nextCarText->getSizeX()/2, 550 - nextCarText->getSizeY()/2);
	nextCarText->setColor(255, 255, 255, 0);
	nextCarText->visible(true);

	prevCarButton = factory->getButton(BUTTON_01);
	prevCarButton->setSize(150, 60);
	prevCarButton->setPos(312 - prevCarButton->getSizeX()/2, 550 - prevCarButton->getSizeY()/2);
	prevCarButton->visible(true);

	prevCarText = factory->getText("Previous", FONT_TITLE_NORMAL);
	prevCarText->setPos(312 - prevCarText->getSizeX()/2, 550 - prevCarText->getSizeY()/2);
	prevCarText->setColor(255, 255, 255, 0);
	prevCarText->visible(true);

	//Initialize level preview
	updateLevelPreview(selectedLevel);

	//Initialize car preview picture
	updateCarPreview(selectedCar);
}

void GameSinglePlayerMenu::release()
{
	delete(frameTimer);
	frameTimer = NULL;

	delete(carPicture);
	carPicture = NULL;

	delete(playernameTextbox);
	playernameTextbox = NULL;

	delete(returnButton);
	returnButton = NULL;

	delete(startButton);
	startButton = NULL;

	delete(nextLevelButton);
	nextLevelButton = NULL;

	delete(prevLevelButton);
	prevLevelButton = NULL;

	delete(nextCarButton);
	nextCarButton = NULL;

	delete(prevCarButton);
	prevCarButton = NULL;

	delete(singlePlayerText);
	singlePlayerText = NULL;

	delete(returnText);
	returnText = NULL;

	delete(startText);
	startText = NULL;

	delete(nextLevelText);
	nextLevelText = NULL;

	delete(prevLevelText);
	prevLevelText = NULL;

	delete(nextCarText);
	nextCarText = NULL;

	delete(prevCarText);
	prevCarText = NULL;

	delete(menuPlayernameText);
	menuPlayernameText = NULL;

	delete(menuLevelText);
	menuLevelText = NULL;

	delete(menuCarText);
	menuCarText = NULL;

	delete(currentLevelText);
	currentLevelText = NULL;
}

void GameSinglePlayerMenu::pause()
{
	this->frameTimer->pause();
}

void GameSinglePlayerMenu::resume()
{
	this->frameTimer->unpause();
}

void GameSinglePlayerMenu::handleEvents(Event* event)
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
					musicPlayer->popMusic();
					stateManager->popState();
				}
				else
				{
					updateNameTextbox(event);
				}
				break;
			case MOUSE_EVENT:
				event->getMousePosition(&mouseX, &mouseY);

				if(event->getLMouseButtonState() == BUTTON_PRESSED)
				{
					mousePressed = true;
				}

				playernameTextbox->checkFocusState(mouseX, mouseY, mousePressed);
				handleButtonsEvents(mouseX, mouseY, mousePressed);
				break;
			default:
				break;
		}
		delete(event);
		event = NULL;
	}
}

void GameSinglePlayerMenu::update()
{
	float timeStep = 0.0f;

	//Calculate time step
	if(!frameTimer->isPaused())
	{
		timeStep = frameTimer->getTicks() / 1000.f;
	}

	background->move(timeStep);
	background->update();

	carPicture->update();

	playernameTextbox->update();

	currentLevelText->update();

	singlePlayerText->update();

	menuPlayernameText->update();
	menuLevelText->update();
	menuCarText->update();

	returnButton->update();
	returnText->update();

	startButton->update();
	startText->update();

	nextLevelButton->update();
	nextLevelText->update();

	prevLevelButton->update();
	prevLevelText->update();

	nextCarButton->update();
	nextCarText->update();

	prevCarButton->update();
	prevCarText->update();

	if(!frameTimer->isPaused())
	{
		frameTimer->start();
	}
}

void GameSinglePlayerMenu::handleButtonsEvents(int mouseX, int mouseY, bool mousePressed)
{
	if(returnButton->checkButtonState(mouseX, mouseY, mousePressed))
	{
		returnButton->playClickSound();
		musicPlayer->popMusic();
		stateManager->popState();
	}
	else if(startButton->checkButtonState(mouseX, mouseY, mousePressed))
	{
		startButton->playClickSound();

		Level* level;
		level = gameManager->getLevel(selectedLevel);

		setPlayer();

		stateManager->setState(new GameLevel(factory, stateManager, gameManager, level));
	}
	else if(nextLevelButton->checkButtonState(mouseX, mouseY, mousePressed))
	{
		nextLevelButton->playClickSound();

		nextLevel();
	}
	else if(prevLevelButton->checkButtonState(mouseX, mouseY, mousePressed))
	{
		prevLevelButton->playClickSound();

		previousLevel();
	}
	else if(nextCarButton->checkButtonState(mouseX, mouseY, mousePressed))
	{
		nextCarButton->playClickSound();

		nextCar();
	}
	else if(prevCarButton->checkButtonState(mouseX, mouseY, mousePressed))
	{
		prevCarButton->playClickSound();

		previousCar();
	}
}

void GameSinglePlayerMenu::nextLevel()
{
	selectedLevel++;

	if(selectedLevel > gameManager->availableLevels())
	{
		selectedLevel = 1;
	}

	updateLevelPreview(selectedLevel);
}

void GameSinglePlayerMenu::previousLevel()
{
	selectedLevel--;

	if(selectedLevel < 1)
	{
		selectedLevel = gameManager->availableLevels();
	}

	updateLevelPreview(selectedLevel);
}

void GameSinglePlayerMenu::nextCar()
{
	selectedCar++;

	if(selectedCar > PLAYERCARS_MAX)
	{
		selectedCar = 1;
	}

	updateCarPreview(selectedCar);
}

void GameSinglePlayerMenu::previousCar()
{
	selectedCar--;

	if(selectedCar < 1)
	{
		selectedCar = PLAYERCARS_MAX;
	}

	updateCarPreview(selectedCar);
}

void GameSinglePlayerMenu::updateLevelPreview(int selectedLevel)
{
	Level* level;

	level = gameManager->getLevel(selectedLevel);

	if(currentLevelText == NULL)
	{
		currentLevelText = factory->getText(level->getName(), FONT_TITLE_LARGE);
		currentLevelText->setColor(255, 255, 255, 0);
		currentLevelText->visible(true);
	}
	else
	{
		currentLevelText->setText(level->getName());
	}

	currentLevelText->setPos(512 - currentLevelText->getSizeX()/2, 280 - currentLevelText->getSizeY()/2);
}

void GameSinglePlayerMenu::updateCarPreview(int selectedCar)
{
	PictureType picture;

	switch(selectedCar)
	{
		case 1:
			picture = PICTURE_CAR_01_TOP;
			break;
		case 2:
			picture = PICTURE_CAR_02_TOP;
			break;
		case 3:
			picture = PICTURE_CAR_03_TOP;
			break;
		case 4:
			picture = PICTURE_CAR_04_TOP;
			break;
		case 5:
			picture = PICTURE_CAR_05_TOP;
			break;
		default:
			picture = PICTURE_CAR_01_TOP;
			break;
	}

	if(carPicture != NULL)
	{
		delete(carPicture);
		carPicture = NULL;
	}

	carPicture = factory->getPicture(picture);
	carPicture->setSize(150, 200);
	carPicture->setPos(512 - carPicture->getSizeX()/2, 540 - carPicture->getSizeY()/2);
	carPicture->visible(true);
}

void GameSinglePlayerMenu::updateNameTextbox(Event* event)
{
	char character;

	if(playernameTextbox->getTextboxState() == TEXTBOX_STATE_ACTIVE && event->getButtonState() == BUTTON_PRESSED)
	{
		if(event->getKeyEvent()->getKeyValue() >= KEY_A && event->getKeyEvent()->getKeyValue() <= KEY_Z)
		{
			character = 'a' + event->getKeyEvent()->getKeyValue() - KEY_A;

			playernameTextbox->addCharacter(character);
		}
		else if(event->getKeyEvent()->getKeyValue() >= KEY_0 && event->getKeyEvent()->getKeyValue() <= KEY_9)
		{
			character = '0' + event->getKeyEvent()->getKeyValue() - KEY_0;

			playernameTextbox->addCharacter(character);
		}
		else if(event->getKeyEvent()->getKeyValue() == KEY_BACKSPACE)
		{
			playernameTextbox->delCharacter();
		}
	}
}

void GameSinglePlayerMenu::setPlayer()
{
	Car* playerCar;
	Player* player;
	CarType type;

	switch(selectedCar)
	{
		case 1:
			type = CAR_PLAYER_01;
			break;
		case 2:
			type = CAR_PLAYER_02;
			break;
		case 3:
			type = CAR_PLAYER_03;
			break;
		case 4:
			type = CAR_PLAYER_04;
			break;
		case 5:
			type = CAR_PLAYER_05;
			break;
		default:
			type = CAR_PLAYER_01;
			break;
	}

	playerCar = factory->getCar(type);
	player = gameManager->getThisPlayer();

	player->setCar(playerCar);
	player->setName(playernameTextbox->getText());
}

/*
 * Game.cpp
 *
 *  Created on: 9-mrt.-2015
 *      Author: Thomas
 */

#include "Game.h"

using namespace CCG;

//Default constructor
Game::Game()
{
	factory = NULL;
	debug = false;
	stateManager = new GameStateManager();
	gameManager = new GameManager();
	configManager = new GameConfigManager();
}

Game::Game(GameFactory* factory)
{
	this->factory = factory;
	this->debug = false;
	stateManager = new GameStateManager();
	gameManager = new GameManager();
	configManager = new GameConfigManager();
}

Game::Game(GameFactory* factory, bool debug)
{
	this->factory = factory;
	this->debug = debug;
	stateManager = new GameStateManager();
	gameManager = new GameManager();
	configManager = new GameConfigManager();
}

Game::~Game()
{
	delete(stateManager);
	delete(gameManager);
	delete(configManager);
}

int Game::launch()
{
	Window* window;
	EventStack* events;
	Cursor* cursor;

	const char* windowTitle = "Car Crash - 2015 Created by Thomas Huybrechts   v.4.13.94 - beta";
	const char* configLocation = ".\\Config.xml";

	if(debug)
		printf("Game launching...\n");

	if(factory->initializeFactory() != 0)
	{
		printf("Error while initializing game factory. Game will abort.");
		return -1;
	}

	//Set-up configurations
	loadConfigurations(configLocation);

	events = factory->getEventStack();

	window = factory->getWindow();
	window->setTitle(windowTitle);
	window->showWindow();
	window->updateWindow();

	cursor = factory->getCursor();

	//Initialize random seed
	srand(time(NULL));

	//Initialize splash screen
	stateManager->setState(new GameSplash(factory, stateManager, gameManager));
	stateManager->getState()->initialize();
	stateManager->update();
	window->updateWindow();

	if(factory->loadAsset() != 0)
	{
		printf("Error while loading assets. Game will abort.");
		factory->releaseFactory();
		return -1;
	}

	Event* event;

	//Main game loop
	while(stateManager->getRunningState())
	{
		//Get all events from the event stack
		event = events->pollEvent();

		while(event != NULL)
		{
			if(event->getType() == MOUSE_EVENT)
			{
				bool mousePressed = false;
				int mouseX, mouseY = 0;

				if(event->getLMouseButtonState() == BUTTON_PRESSED)
				{
					mousePressed = true;
				}

				event->getMousePosition(&mouseX, &mouseY);

				cursor->setCursorPosition(mouseX, mouseY, mousePressed);
			}

			stateManager->handleEvents(event);

			event = events->pollEvent();
		}

		stateManager->update();

		cursor->update();

		window->updateWindow();
	}

	stateManager->releaseStack();

	if(debug)
		printf("Game exiting...\n");

	//Save configuration
	saveConfigurations(configLocation);

	if(factory->releaseFactory())
	{
		printf("Error while closing factory engine.");
		return -1;
	}
	return 0;
}

void Game::loadConfigurations(const char* configLocation)
{
	GameSettings* settings;

	//Load configuration, if not available create config-file
	if(configManager->loadConfig(configLocation) != 0)
	{
		if(configManager->saveConfig(configLocation) != 0)
		{
			printf("Error while creating configuration file! Changes will not be saved.");
		}
	}

	settings = configManager->getSettings();

	factory->getMusicPlayer()->setMusicVolume(settings->getMusicVolume());
	factory->getMusicPlayer()->setSFXVolume(settings->getSFXVolume());
	factory->getWindow()->setVSync(settings->getVSyncActive());
	factory->getWindow()->setFPSCap(settings->getFPSCap());

	gameManager->getThisPlayer()->setControls(settings->getControlsPlayer(1));
}

void Game::saveConfigurations(const char* configLocation)
{
	GameSettings* newSettings = new GameSettings();

	//Save configuration
	newSettings->setMusicVolume(factory->getMusicPlayer()->getMusicVolume());
	newSettings->setSFXVolume(factory->getMusicPlayer()->getSFXVolume());
	newSettings->setVSync(factory->getWindow()->getVSync());
	newSettings->setFPSCap(factory->getWindow()->getFPSCap());

	newSettings->setControlsPlayer(gameManager->getThisPlayer()->getControls(), 1);

	configManager->setSettings(newSettings);

	if(configManager->saveConfig(configLocation) != 0)
	{
		printf("Error while saving configuration file! Changes will be lost.");
	}
}

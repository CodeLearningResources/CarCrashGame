/*
 * GameOptionsMenu.cpp
 *
 *  Created on: 17-apr.-2015
 *      Author: Thomas
 */

#include "GameOptionsMenu.h"

using namespace CCG;

GameOptionsMenu::GameOptionsMenu() : GameState()
{
	prevMusicVolume = 0;
	prevSFXVolume = 0;
	prevFPSCap = 0;
	prevVSyncActive = false;
}

GameOptionsMenu::GameOptionsMenu(GameFactory* factory, GameStateManager* stateManager, GameManager* gameManager, Background* background) : GameState(factory, stateManager, gameManager)
{
	this->background = background;
	this->prevMusicVolume = 0;
	this->prevSFXVolume = 0;
	this->prevFPSCap = 0;
	this->prevVSyncActive = false;
}

GameOptionsMenu::~GameOptionsMenu()
{

}

void GameOptionsMenu::initialize()
{
	frameTimer = factory->getTimer();
	gameWindow = factory->getWindow();
	factory->getCursor()->visible(true);

	//Initialize music player
	musicPlayer = factory->getMusicPlayer();
	musicPlayer->pushMusic(factory->getMusic(MUSIC_OPTIONS));
	musicPlayer->startMusic(true);

	//Get current options states
	prevMusicVolume = musicPlayer->getMusicVolume();
	prevSFXVolume = musicPlayer->getSFXVolume();
	prevFPSCap = gameWindow->getFPSCap();
	prevVSyncActive = gameWindow->getVSync();

	//Initialize options text
	optionsText = factory->getText("OPTIONS", FONT_TITLE_LARGE);
	optionsText->setPos(512 - optionsText->getSizeX()/2, 150 - optionsText->getSizeY()/2);
	optionsText->setColor(255, 255, 255, 0);
	optionsText->visible(true);

	musicText = factory->getText("Music", FONT_TITLE_NORMAL);
	musicText->setPos(150, 250 - musicText->getSizeY()/2);
	musicText->setColor(255, 255, 255, 0);
	musicText->visible(true);

	sfxText = factory->getText("SFX", FONT_TITLE_NORMAL);
	sfxText->setPos(150, 300 - sfxText->getSizeY()/2);
	sfxText->setColor(255, 255, 255, 0);
	sfxText->visible(true);

	//Initialize buttons
	controlsButton = factory->getButton(BUTTON_01);
	controlsButton->setSize(185, 60);
	controlsButton->setPos(380 - controlsButton->getSizeX()/2, 435 - controlsButton->getSizeY()/2);
	controlsButton->visible(true);

	controlsText = factory->getText("Controls", FONT_TITLE_NORMAL);
	controlsText->setPos(380 - controlsText->getSizeX()/2, 435 - controlsText->getSizeY()/2);
	controlsText->setColor(255, 255, 255, 0);
	controlsText->visible(true);

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

	//Initialize sliders
	musicVolumeSlider = factory->getSlider(SLIDER_01);
	musicVolumeSlider->setSize(450, 35);
	musicVolumeSlider->setPos(512 - musicVolumeSlider->getSizeX()/2, 250 - musicVolumeSlider->getSizeY()/2);
	musicVolumeSlider->visible(true);

	musicValueText = factory->getText("100", FONT_TITLE_NORMAL);
	musicValueText->setPos(785 - musicValueText->getSizeX()/2, 250 - musicValueText->getSizeY()/2);
	musicValueText->setColor(255, 255, 255, 0);
	musicValueText->visible(true);

	sfxVolumeSlider = factory->getSlider(SLIDER_01);
	sfxVolumeSlider->setSize(450, 35);
	sfxVolumeSlider->setPos(512 - sfxVolumeSlider->getSizeX()/2, 300 - sfxVolumeSlider->getSizeY()/2);
	sfxVolumeSlider->visible(true);

	sfxValueText = factory->getText("100", FONT_TITLE_NORMAL);
	sfxValueText->setPos(785 - sfxValueText->getSizeX()/2, 300 - sfxValueText->getSizeY()/2);
	sfxValueText->setColor(255, 255, 255, 0);
	sfxValueText->visible(true);

	//Initialize checkboxes
	vSyncCheckbox = factory->getCheckbox(CHECKBOX_01);
	vSyncCheckbox->setSize(40, 40);
	vSyncCheckbox->setPos(308 - vSyncCheckbox->getSizeX()/2, 360 - vSyncCheckbox->getSizeY()/2);
	vSyncCheckbox->visible(false);
	vSyncCheckbox->setInactive(true);

	vSyncText = factory->getText("VSync", FONT_TITLE_NORMAL);
	vSyncText->setPos(370 - vSyncText->getSizeX()/2, 360 - vSyncText->getSizeY()/2);
	vSyncText->setColor(255, 255, 255, 0);
	vSyncText->visible(false);

	fpsCapCheckbox = factory->getCheckbox(CHECKBOX_01);
	fpsCapCheckbox->setSize(40, 40);
	fpsCapCheckbox->setPos(308 - fpsCapCheckbox->getSizeX()/2, 360 - fpsCapCheckbox->getSizeY()/2);
	fpsCapCheckbox->visible(true);

	fpsCapText = factory->getText("FPS Cap: 60", FONT_TITLE_NORMAL);
	fpsCapText->setPos(405 - fpsCapText->getSizeX()/2, 360 - fpsCapText->getSizeY()/2);
	fpsCapText->setColor(255, 255, 255, 0);
	fpsCapText->visible(true);

	updateValues();
}

void GameOptionsMenu::release()
{
	delete(frameTimer);
	frameTimer = NULL;

	delete(controlsButton);
	controlsButton = NULL;

	delete(applyButton);
	applyButton = NULL;

	delete(cancelButton);
	cancelButton = NULL;

	delete(musicVolumeSlider);
	musicVolumeSlider = NULL;

	delete(sfxVolumeSlider);
	sfxVolumeSlider = NULL;

	delete(vSyncCheckbox);
	vSyncCheckbox = NULL;

	delete(fpsCapCheckbox);
	fpsCapCheckbox = NULL;

	delete(optionsText);
	optionsText = NULL;

	delete(musicText);
	musicText = NULL;

	delete(musicValueText);
	musicValueText = NULL;

	delete(sfxValueText);
	sfxValueText = NULL;

	delete(vSyncText);
	vSyncText = NULL;

	delete(controlsText);
	controlsText = NULL;

	delete(fpsCapCheckbox);
	fpsCapCheckbox = NULL;

	delete(applyText);
	applyText = NULL;

	delete(cancelText);
	cancelText = NULL;
}

void GameOptionsMenu::pause()
{
	this->frameTimer->pause();
}

void GameOptionsMenu::resume()
{
	this->frameTimer->unpause();
}

void GameOptionsMenu::handleEvents(Event* event)
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
					restoreSettings();

					musicPlayer->popMusic();
					stateManager->popState();
				}
				break;
			case MOUSE_EVENT:
				event->getMousePosition(&mouseX, &mouseY);

				if(event->getLMouseButtonState() == BUTTON_PRESSED)
				{
					mousePressed = true;
				}

				handleSliderEvents(mouseX, mouseY, mousePressed);
				handleCheckboxEvents(mouseX, mouseY, mousePressed);
				handleButtonsEvents(mouseX, mouseY, mousePressed);
				break;
			default:
				break;
		}
		delete(event);
		event = NULL;
	}
}

void GameOptionsMenu::updateValues()
{
	char stringValue[4];

	musicVolumeSlider->setValue(musicPlayer->getMusicVolume());
	sprintf(stringValue, "%d", musicVolumeSlider->getValue());
	musicValueText->setText(stringValue);

	sfxVolumeSlider->setValue(musicPlayer->getSFXVolume());
	sprintf(stringValue, "%d", sfxVolumeSlider->getValue());
	sfxValueText->setText(stringValue);

	if(prevFPSCap == 0)
	{
		fpsCapCheckbox->setChecked(false);
	}
	else
	{
		fpsCapCheckbox->setChecked(true);
	}

	vSyncCheckbox->setChecked(prevVSyncActive);
}

void GameOptionsMenu::update()
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
	musicText->update();
	sfxText->update();

	controlsButton->update();
	controlsText->update();

	applyButton->update();
	applyText->update();

	cancelButton->update();
	cancelText->update();

	musicVolumeSlider->update();
	musicValueText->update();

	sfxVolumeSlider->update();
	sfxValueText->update();

	vSyncCheckbox->update();
	vSyncText->update();

	fpsCapCheckbox->update();
	fpsCapText->update();

	if(!frameTimer->isPaused())
	{
		frameTimer->start();
	}
}

void GameOptionsMenu::restoreSettings()
{
	musicPlayer->setMusicVolume(this->prevMusicVolume);
	musicPlayer->setSFXVolume(this->prevSFXVolume);
	gameWindow->setVSync(this->prevVSyncActive);
	gameWindow->setFPSCap(this->prevFPSCap);
}

void GameOptionsMenu::handleButtonsEvents(int mouseX, int mouseY, bool mousePressed)
{
	if(controlsButton->checkButtonState(mouseX, mouseY, mousePressed))
	{
		controlsButton->playClickSound();

		stateManager->pushState(new GameControlsMenu(factory, stateManager, gameManager, background));
	}
	else if(applyButton->checkButtonState(mouseX, mouseY, mousePressed))
	{
		applyButton->playClickSound();

		musicPlayer->popMusic();
		stateManager->popState();
	}
	else if(cancelButton->checkButtonState(mouseX, mouseY, mousePressed))
	{
		cancelButton->playClickSound();

		restoreSettings();

		musicPlayer->popMusic();
		stateManager->popState();
	}
}

void GameOptionsMenu::handleSliderEvents(int mouseX, int mouseY, bool mousePressed)
{
	char stringValue[4];

	if(musicVolumeSlider->checkSliderState(mouseX, mouseY, mousePressed))
	{
		musicPlayer->setMusicVolume(musicVolumeSlider->getValue());

		sprintf(stringValue, "%d", musicVolumeSlider->getValue());
		musicValueText->setText(stringValue);
	}
	else if(sfxVolumeSlider->checkSliderState(mouseX, mouseY, mousePressed))
	{
		musicPlayer->setSFXVolume(sfxVolumeSlider->getValue());

		sprintf(stringValue, "%d", sfxVolumeSlider->getValue());
		sfxValueText->setText(stringValue);
	}
}

void GameOptionsMenu::handleCheckboxEvents(int mouseX, int mouseY, bool mousePressed)
{
	if(vSyncCheckbox->checkCheckboxState(mouseX, mouseY, mousePressed))
	{
		//gameWindow->setVSync(vSyncCheckbox->getCheckState());
		gameWindow->setHardwareAcceleration(false);
	}
	else if(fpsCapCheckbox->checkCheckboxState(mouseX, mouseY, mousePressed))
	{
		if(fpsCapCheckbox->getCheckState())
		{
			gameWindow->setFPSCap(60);
		}
		else
		{
			gameWindow->setFPSCap(0);
		}
	}
}

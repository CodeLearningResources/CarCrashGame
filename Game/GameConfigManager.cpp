/*
 * GameConfigParser.cpp
 *
 *  Created on: 20-jun.-2015
 *      Author: Thomas
 */

#include "GameConfigManager.h"

using namespace CCG;

GameConfigManager::GameConfigManager()
{
	settings = new GameSettings();
}

GameConfigManager::~GameConfigManager()
{
	if(settings)
		delete(settings);

	settings = NULL;
}

int GameConfigManager::loadConfig(const char* fileLocation)
{
	CCG_XML::XMLFileReader* XMLReader = new CCG_XML::XMLFileReader();
	CCG_XML::XMLNode* rootNode;

	if(XMLReader->setFileLocation(fileLocation) != 0)
	{
		//Could not open file
		delete(XMLReader);

		return -1;
	}

	//Save to file
	int result = XMLReader->loadXML();

	if(result != 0)
	{
		//Error during reading file
		delete(XMLReader);
	}

	//Get the resulting configuration from the reader
	rootNode = XMLReader->getRootTree();

	if(rootNode != NULL)
	{
		if(strcmp(rootNode->getElementName()->c_str(), "CCG_Settings") != 0)
		{
			//No config file loaded
			delete(XMLReader);

			return -2;
		}

		std::list<CCG_XML::XMLNode*>::iterator itNode = rootNode->getElements()->begin();

		//Read the configuration tree
		while(itNode != rootNode->getElements()->end())
		{
			std::string* elementName = (*itNode)->getElementName();

			if(strcmp(elementName->c_str(), "MusicVolume") == 0)
			{
				this->settings->setMusicVolume(atoi((*itNode)->getValue()->c_str()));
			}
			else if(strcmp(elementName->c_str(), "SFXVolume") == 0)
			{
				this->settings->setSFXVolume(atoi((*itNode)->getValue()->c_str()));
			}
			else if(strcmp(elementName->c_str(), "FPSCap") == 0)
			{
				this->settings->setFPSCap(atoi((*itNode)->getValue()->c_str()));
			}
			else if(strcmp(elementName->c_str(), "VSync") == 0)
			{
				if(strcmp((*itNode)->getValue()->c_str(), "True") == 0)
				{
					this->settings->setVSync(true);
				}
				else if(strcmp((*itNode)->getValue()->c_str(), "False") == 0)
				{
					this->settings->setVSync(false);
				}
			}
			else if(strcmp(elementName->c_str(), "Controls_Player01") == 0)
			{
				//Read the player controls
				std::list<CCG_XML::XMLNode*>::iterator itControlsNode = (*itNode)->getElements()->begin();
				KeyboardKey** playerControls = new KeyboardKey*[PLAYER_CONTROL_MAX]();

				while(itControlsNode != (*itNode)->getElements()->end())
				{
					std::string* controlName = (*itControlsNode)->getElementName();

					if(strcmp(controlName->c_str(), "Up") == 0)
					{
						playerControls[PLAYER_CONTROL_UP] = new KeyboardKey((KeyboardValue)(atoi((*itControlsNode)->getValue()->c_str())));
					}
					else if(strcmp(controlName->c_str(), "Down") == 0)
					{
						playerControls[PLAYER_CONTROL_DOWN] = new KeyboardKey((KeyboardValue)(atoi((*itControlsNode)->getValue()->c_str())));
					}
					else if(strcmp(controlName->c_str(), "Left") == 0)
					{
						playerControls[PLAYER_CONTROL_LEFT] = new KeyboardKey((KeyboardValue)(atoi((*itControlsNode)->getValue()->c_str())));
					}
					else if(strcmp(controlName->c_str(), "Right") == 0)
					{
						playerControls[PLAYER_CONTROL_RIGHT] = new KeyboardKey((KeyboardValue)(atoi((*itControlsNode)->getValue()->c_str())));
					}
					else if(strcmp(controlName->c_str(), "Fire_Rocket") == 0)
					{
						playerControls[PLAYER_CONTROL_ROCKET] = new KeyboardKey((KeyboardValue)(atoi((*itControlsNode)->getValue()->c_str())));
					}

					itControlsNode++;
				}

				//Check if each control is binded
				bool checked = true;

				for(int i = 0; i < PLAYER_CONTROL_MAX; i++)
				{
					if(playerControls[i] == NULL)
					{
						checked = false;
					}
				}

				if(checked)
				{
					this->settings->setControlsPlayer(playerControls, 1);
				}

				for(int i = 0; i < PLAYER_CONTROL_MAX; i++)
				{
					if(playerControls[i])
						delete(playerControls[i]);

					playerControls[i] = NULL;
				}

				delete(playerControls);
			}
			else
			{
				//Options not recognized, skip
			}

			itNode++;
		}
	}

	return 0;
}

int GameConfigManager::saveConfig(const char* fileLocation)
{
	char* buffer = new char[1024]();

	CCG_XML::XMLFileWriter* XMLWriter = new CCG_XML::XMLFileWriter();

	if(XMLWriter->setFileLocation(fileLocation) != 0)
	{
		//Could not open file
		delete(XMLWriter);

		return -1;
	}

	//Create XML tree for saving to config file
	CCG_XML::XMLNode* rootNode = new CCG_XML::XMLNode("CCG_Settings");

	//Create elements for settings
	CCG_XML::XMLNode* musicNode = new CCG_XML::XMLNode("MusicVolume");
	sprintf(buffer, "%d", this->settings->getMusicVolume());
	musicNode->setValue(new std::string(buffer));

	CCG_XML::XMLNode* SFXNode = new CCG_XML::XMLNode("SFXVolume");
	sprintf(buffer, "%d", this->settings->getSFXVolume());
	SFXNode->setValue(new std::string(buffer));

	CCG_XML::XMLNode* FPSCapNode = new CCG_XML::XMLNode("FPSCap");
	sprintf(buffer, "%d", this->settings->getFPSCap());
	FPSCapNode->setValue(new std::string(buffer));

	CCG_XML::XMLNode* VSyncNode = new CCG_XML::XMLNode("VSync");
	if(this->settings->getVSyncActive())
	{
		VSyncNode->setValue(new std::string("True"));
	}
	else
	{
		VSyncNode->setValue(new std::string("False"));
	}

	//Create elements for controls
	CCG_XML::XMLNode* controlsNode = new CCG_XML::XMLNode("Controls_Player01");

	CCG_XML::XMLNode* controlUpNode = new CCG_XML::XMLNode("Up");
	sprintf(buffer, "%d", (int)this->settings->getControlsPlayer(1)[PLAYER_CONTROL_UP]->getKeyValue());
	controlUpNode->setValue(new std::string(buffer));

	CCG_XML::XMLNode* controlDownNode = new CCG_XML::XMLNode("Down");
	sprintf(buffer, "%d", (int)this->settings->getControlsPlayer(1)[PLAYER_CONTROL_DOWN]->getKeyValue());
	controlDownNode->setValue(new std::string(buffer));

	CCG_XML::XMLNode* controlLeftNode = new CCG_XML::XMLNode("Left");
	sprintf(buffer, "%d", (int)this->settings->getControlsPlayer(1)[PLAYER_CONTROL_LEFT]->getKeyValue());
	controlLeftNode->setValue(new std::string(buffer));

	CCG_XML::XMLNode* controlRightNode = new CCG_XML::XMLNode("Right");
	sprintf(buffer, "%d", (int)this->settings->getControlsPlayer(1)[PLAYER_CONTROL_RIGHT]->getKeyValue());
	controlRightNode->setValue(new std::string(buffer));

	CCG_XML::XMLNode* controlRocketNode = new CCG_XML::XMLNode("Fire_Rocket");
	sprintf(buffer, "%d", (int)this->settings->getControlsPlayer(1)[PLAYER_CONTROL_ROCKET]->getKeyValue());
	controlRocketNode->setValue(new std::string(buffer));

	//Assign controls elements to controls node
	controlsNode->addElement(controlUpNode);
	controlsNode->addElement(controlDownNode);
	controlsNode->addElement(controlLeftNode);
	controlsNode->addElement(controlRightNode);
	controlsNode->addElement(controlRocketNode);

	//Assign elements to root
	rootNode->addElement(musicNode);
	rootNode->addElement(SFXNode);
	rootNode->addElement(FPSCapNode);
	rootNode->addElement(VSyncNode);
	rootNode->addElement(controlsNode);

	//Save to file
	XMLWriter->setRootTree(rootNode);
	int result = XMLWriter->saveXML();

	//Close XML file, and delete XML tree
	delete(XMLWriter);

	delete(buffer);

	return result;
}

GameSettings* GameConfigManager::getSettings()
{
	return this->settings;
}

void GameConfigManager::setSettings(GameSettings* settings)
{
	*this->settings = *settings;
}

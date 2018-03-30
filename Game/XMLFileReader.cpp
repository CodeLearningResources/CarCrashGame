/*
 * XMLFileReader.cpp
 *
 *  Created on: 20-jun.-2015
 *      Author: Thomas
 */

#include "XMLFileReader.h"

using namespace CCG_XML;

XMLFileReader::XMLFileReader()
{
	rootNode = NULL;
	file = NULL;
}

XMLFileReader::~XMLFileReader()
{
	if(rootNode)
		delete(rootNode);

	rootNode = NULL;

	if(file)
		fclose(file);
}

int XMLFileReader::setFileLocation(const char* fileLocation)
{
	if(fileLocation == NULL)
	{
		//No file location specified
		return -1;
	}

	file = fopen(fileLocation, "r");

	if(file == NULL)
	{
		//File could not be opened
		return -1;
	}
	else
	{
		return 0;
	}
}

XMLNode* XMLFileReader::getRootTree()
{
	return this->rootNode;
}

int XMLFileReader::loadXML()
{
	if(file == NULL)
	{
		//No file is opened!
		return -1;
	}

	//Clear XML tree if existing
	if(rootNode)
		delete(rootNode);

	//Set root node
	char* buffer = new char[1024]();
	char* valuePointer;

	fgets(buffer, 1024, file);

	if(strchr(buffer, '<') == NULL)
	{
		//File is not valid!
		delete(buffer);

		return -2;
	}

	valuePointer = strtok(buffer, "\t<>");

	if(valuePointer == NULL)
	{
		//EOF, file is corrupted?
		delete(buffer);

		return -2;
	}

	rootNode = new XMLNode((std::string)valuePointer);

	//Read elements from file
	loadElement(rootNode);

	return 0;
}

int XMLFileReader::loadElement(XMLNode* node)
{
	char* buffer = new char[1024]();
	char* valuePointer;
	bool elementFinished = false;

	if(node == NULL)
	{
		//Node is NULL
		return -2;
	}

	//Read value or child elements
	fgets(buffer, 1024, file);

	if(strchr(buffer, '<') == NULL)
	{
		valuePointer = strtok(buffer, "\t<>");
		if(valuePointer != NULL)
		{
			//Read value
			node->setValue(new std::string(valuePointer));
		}

		//Skip element ending
		fgets(buffer, 1024, file);
	}
	else
	{
		//Read child element
		while(!elementFinished)
		{
			if(strchr(buffer, '/') == NULL)
			{
				//Add child element
				valuePointer = strtok(buffer, "\t<>");

				if(valuePointer == NULL)
				{
					//EOF, file is corrupted?
					delete(buffer);

					return -3;
				}

				XMLNode* newChildNode = new XMLNode((std::string)valuePointer);

				node->addElement(newChildNode);

				int result = loadElement(newChildNode);

				if(result != 0)
				{
					//Error occurred, stop load procedure
					delete(buffer);

					return result;
				}

				//Read next line
				fgets(buffer, 1024, file);
			}
			else
			{
				//End of element
				elementFinished = true;
			}
		}
	}

	delete(buffer);

	return 0;
}

/*
 * XMLFileWriter.cpp
 *
 *  Created on: 20-jun.-2015
 *      Author: Thomas
 */

#include "XMLFileWriter.h"

using namespace CCG_XML;

XMLFileWriter::XMLFileWriter()
{
	rootNode = NULL;
	file = NULL;
}

XMLFileWriter::~XMLFileWriter()
{
	if(rootNode)
		delete(rootNode);

	rootNode = NULL;

	if(file)
		fclose(file);
}

int XMLFileWriter::setFileLocation(const char* fileLocation)
{
	if(fileLocation == NULL)
	{
		//No file location specified
		return -1;
	}

	file = fopen(fileLocation, "w");

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

void XMLFileWriter::setRootTree(XMLNode* root)
{
	//Delete previous root
	if(this->rootNode)
		delete(this->rootNode);

	this->rootNode = root;
}

int XMLFileWriter::saveXML()
{
	int level = 0;

	if(file == NULL)
	{
		//No file is opened!
		return -1;
	}

	if(rootNode == NULL)
	{
		//No root node available!
		return -2;
	}

	//Write elements to file
	writeElement(rootNode, &level);

	return 0;
}

void XMLFileWriter::writeElement(XMLNode* node, int* level)
{
	char* buffer = new char[1024]();

	if(node == NULL)
	{
		return;
	}

	//Add tabs for correct spacing according to level
	for(int i = 0; i < *level; i++)
	{
		fputs("\t", file);
	}

	//Write element opening
	sprintf(buffer, "<%s>\n", node->getElementName()->c_str());
	fputs(buffer, file);

	//Add level
	(*level)++;

	//Write value or add elements
	if(node->getValue() != NULL)
	{
		//Add tabs for correct spacing
		for(int i = 0; i < *level; i++)
		{
			fputs("\t", file);
		}

		//Write value
		sprintf(buffer, "%s\n", node->getValue()->c_str());
		fputs(buffer, file);
	}
	else
	{
		if(!node->getElements()->empty())
		{
			std::list<XMLNode*>::iterator itNode = node->getElements()->begin();

			while(itNode != node->getElements()->end())
			{
				writeElement(*itNode, level);

				itNode++;
			}
		}
	}

	//Subtract level
	(*level)--;

	//Write element closing
	for(int i = 0; i < *level; i++)
	{
		fputs("\t", file);
	}

	sprintf(buffer, "</%s>\n", node->getElementName()->c_str());
	fputs(buffer, file);

	delete(buffer);
}


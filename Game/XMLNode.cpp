/*
 * XMLNode.cpp
 *
 *  Created on: 20-jun.-2015
 *      Author: Thomas
 */

#include "XMLNode.h"

using namespace CCG_XML;

XMLNode::XMLNode()
{
	value = NULL;
	elementName = "";
	elements = new std::list<XMLNode*>();
}

XMLNode::XMLNode(std::string name)
{
	this->value = NULL;
	this->elementName = name;
	this->elements = new std::list<XMLNode*>();
}

XMLNode::XMLNode(const XMLNode& node)
{
	this->value = new std::string(*node.value);
	this->elementName = node.elementName;
	this->elements = node.elements;
}

XMLNode::~XMLNode()
{
	std::list<XMLNode*>::iterator itNode = elements->begin();

	if(value)
		delete(value);

	value = NULL;

	while(itNode != elements->end())
	{
		itNode = elements->erase(itNode);
	}

	delete(elements);
	elements = NULL;
}

void XMLNode::setValue(std::string* value)
{
	this->value = value;
}

void XMLNode::setElementName(std::string name)
{
	this->elementName = name;
}

void XMLNode::addElement(XMLNode* element)
{
	this->elements->push_back(element);
}

std::string* XMLNode::getValue()
{
	return this->value;
}

std::string* XMLNode::getElementName()
{
	return &this->elementName;
}

std::list<XMLNode*>* XMLNode::getElements()
{
	return this->elements;
}

/*
 * XMLNode.h
 *
 *  Created on: 20-jun.-2015
 *      Author: Thomas
 */

#ifndef GAME_XMLNODE_H_
#define GAME_XMLNODE_H_

#include <string>
#include <list>

namespace CCG_XML
{
	/*
	 * Node class to define a element in XML. A element can only contain a value or a collection of child nodes, not both!
	 */
	class XMLNode
	{
		public:
			/*
			 * Constructor
			 * @param name Set the name of the node (element)
			 */
			XMLNode(std::string name);

			/*
			 * Copy constructor
			 */
			XMLNode(const XMLNode& node);

			/*
			 * Destructor
			 */
			virtual ~XMLNode(void);

			/*
			 * Set the value of the element
			 * @param value Text value
			 */
			void setValue(std::string* value);

			/*
			 * Set the name of the node (element)
			 * @name Name of the node
			 */
			void setElementName(std::string name);

			/*
			 * Add a child node to the element
			 * @element Child node
			 */
			void addElement(XMLNode* element);

			//Get methods
			std::string* getValue(void);
			std::string* getElementName(void);
			std::list<XMLNode*>* getElements(void);

		private:
			std::string* value;
			std::string elementName;
			std::list<XMLNode*>* elements;

		protected:
			XMLNode(void);
	};
}

#endif /* GAME_XMLNODE_H_ */

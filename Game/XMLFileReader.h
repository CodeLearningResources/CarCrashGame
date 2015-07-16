/*
 * XMLFileReader.h
 *
 *  Created on: 20-jun.-2015
 *      Author: Thomas
 */

#ifndef GAME_XMLFILEREADER_H_
#define GAME_XMLFILEREADER_H_

#include <stdio.h>
#include <string.h>

#include "XMLNode.h"

namespace CCG_XML
{
 	/*
 	 * Class for parsing a XML tree from a XML file
 	 */
	class XMLFileReader
	{
		public:
			XMLFileReader(void);
			virtual ~XMLFileReader(void);

			/*
			 * Set the file location to read
			 * @return 0 if successful, -1 if file couldn't be opened or doesn't exist
			 */
			int setFileLocation(const char* fileLocation);

			/*
			 * Return the XML tree
			 * @return the root of the XML tree, or NULL if no XML file was read
			 */
			XMLNode* getRootTree(void);

			/*
			 * Read the selected XML file and create a XML tree
			 * @return 0 if succeeded, -1 if file could not be opened, -2 if file could not be interpreted (corrupted file)
			 */
			int loadXML(void);

		private:
			XMLNode* rootNode;					//XML tree
			FILE* file;							//XML file

			int loadElement(XMLNode* node);		//Get next XMLNode
	};
}

#endif /* GAME_XMLFILEREADER_H_ */

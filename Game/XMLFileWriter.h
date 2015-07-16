/*
 * XMLFileWriter.h
 *
 *  Created on: 20-jun.-2015
 *      Author: Thomas
 */

#ifndef GAME_XMLFILEWRITER_H_
#define GAME_XMLFILEWRITER_H_

#include <stdio.h>

#include "XMLNode.h"

namespace CCG_XML
{
	/*
	 * Class for parsing a XML file from a XML tree
	 */
	class XMLFileWriter
	{
		public:
			XMLFileWriter(void);
			virtual ~XMLFileWriter(void);

			/*
			 * Set the file location to write
			 * @return 0 if successful, -1 if file couldn't be opened or created
			 */
			int setFileLocation(const char* fileLocation);

			/*
			 * Set the root of the XML tree to be written to the file
			 * @param root The XML root node of the XML tree
			 */
			void setRootTree(XMLNode* root);

			/*
			 * Write the selected XML tree to the selected file
			 * @return 0 if succeeded, -1 if file could not be made, -2 if settings are not set in the manager
			 */
			int saveXML(void);

		private:
			XMLNode* rootNode;			//XML tree
			FILE* file;					//XML file

			void writeElement(XMLNode* node, int* level);		//Write next XMLNode
	};
}

#endif /* GAME_XMLFILEWRITER_H_ */

#include "XMLReader.h"
#include <string>

XMLReader::XMLReader(const char* strTage)
{
	readfile(strTage);
}

xmltage XMLReader::makeXMLTage(const char* strTage) const
{
	xmltage xmlTage;
	std::string tag = strTage;
	size_t index = 0;

	// Cutting the gaps at the beginning and at the end
	size_t startPos = tag.find_first_not_of(" ");
	tag.erase(0, startPos);
	size_t endPos = tag.find_last_not_of(" ");
	tag.erase(endPos + 1, tag.size() - endPos + 1);

	// Checking the flag
	if (tag[0] == '/') {
		xmlTage.flag = xmltage::END_TAG;
		tag.erase(0, 1);
	}
	else if (tag[tag.size() - 1] == '/') {
		xmlTage.flag = xmltage::EMPTY_TAG;
		if (tag[tag.size() - 2] == ' ')
		{
			size_t endPos = tag.find_last_of(" ");
			tag.erase(endPos, tag.size() - endPos);
		}
		else {
			tag.erase(tag.size() - 1, 1);
		}
	}
	else
	{
		xmlTage.flag = xmltage::INITIAL_TAG;
	}

	// Tag name
	size_t endNamePos = tag.find_first_of(" ");
	xmlTage.name = tag.substr(0, endNamePos);
	tag.erase(0, endNamePos);


	while (tag.size() != 0) {
		// Start checking attributes
		std::pair<std::string, std::string> att;
		size_t startAttPos = tag.find_first_not_of(" ");
		tag.erase(0, startAttPos);

		size_t endNameAttPos = tag.find_first_of(" =");
		att.first = tag.substr(0, endNameAttPos);
		tag.erase(0, endNameAttPos);

		size_t startValPos = tag.find_first_of("\"\'");
		size_t endValPos = 0;
		if (tag[startValPos] == '\"') {
			endValPos = tag.find_first_of('\"', startValPos + 1);
		}
		else if (tag[startValPos] == '\'') {
			endValPos = tag.find_first_of('\'', startValPos + 1);
		}
		std::string val = tag.substr(startValPos + 1, endValPos - startValPos - 1);
		tag.erase(0, endValPos+1);
		att.second = val;

		xmlTage.attributes.insert(att);
	}

	return xmlTage;
}

inline xmltage XMLReader::makeXMLTage(std::string strTage) const
{
	return makeXMLTage(strTage.c_str());
}

bool XMLReader::readfile(const char* nameFile)
{
	std::ifstream fXML(nameFile, std::ifstream::in);

	if (fXML.fail()) {
		std::cout << "File opening error." << std::endl;
		return false;
	}

	std::string strTage;
	while (fXML.good())
	{
		std::getline(fXML, strTage, '<');
		std::getline(fXML, strTage, '>');

		if (strTage.size() != 0) {
			dataXML.push_back(makeXMLTage(strTage));
		}
	}

	return true;
}

const DataXML& XMLReader::getDataXML() const
{
	return dataXML;
}

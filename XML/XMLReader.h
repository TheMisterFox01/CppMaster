#pragma once
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>

typedef struct xmltage {
	std::string name;
	std::map<std::string,std::string> attributes;
	enum flag {
		INITIAL_TAG,	// <elem>
		END_TAG,		// </elem>
		EMPTY_TAG		// <elem/>
	} flag;
}xmltage;

typedef std::vector<xmltage> DataXML;

class XMLReader
{
	DataXML dataXML;

public:
	XMLReader() = default;
	XMLReader(const char* strTage);

	~XMLReader() = default;
private:
	xmltage makeXMLTage(const char* strTage) const;
	xmltage makeXMLTage(std::string strTage) const;
public:
	bool readfile(const char* nameFile);
	const DataXML& getDataXML() const;
};
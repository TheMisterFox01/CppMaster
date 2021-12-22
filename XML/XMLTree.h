#pragma once
#include "Tree.h"
#include "XMLReader.h"

class XMLTree : public Tree, private XMLReader
{
public:
	XMLTree();
	XMLTree(const char* nameFile);
	~XMLTree();

	void createTXMLTree(const char* nameFile);
};
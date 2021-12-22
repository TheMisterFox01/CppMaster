#include <iostream>
#include "TreeForXML.h"

using namespace std;

int main()
{
	TreeForXML* txml = new TreeForXML("tree.xml");
	txml->print();
	delete txml;

	return 0;
}

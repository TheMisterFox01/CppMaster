#include "XMLTree.h"

XMLTree::XMLTree(const char* nameFile)
{
	createXMLTree(nameFile);
}

void TreeForXML::createXMLTree(const char* nameFile)
{
	if(!readfile(nameFile)) return;
	
	DataXML xml = getDataXML();
	tree_node* node = NULL;

	for (xmltage tag : xml) {
		if (tag.name == "node") {
			if (tag.flag == xmltage::flag::END_TAG) {
				if(node != NULL && node->parent != NULL)
					node = node->parent;
			}
			else {
				std::string var;
				std::map<std::string, std::string> att = tag.attributes;
				std::map<std::string, std::string>::iterator it;
				it = att.find("var");
				if (it != att.end()) {
					var = it->second;
				}
				else {
					var = "empty";
				}

				if (node == NULL) {
					node = new tree_node;
					node->parent = NULL;
					node->data = var;
				}
				else
				{
					tree_node* nNode = new tree_node;
					nNode->parent = node;
					nNode->data = var;
					node->nodes.push_back(nNode);
					if (tag.flag == xmltage::flag::INITIAL_TAG)
						node = nNode;
				}
			}
		}
	}

	head = node;
}

#include <vector>
#include <iomanip> 
#include "Tree.h"
Tree::Tree():head(NULL)
{

}

Tree::~Tree()
{
	destroyTree(head);
	delete head;
}

void destroyTree(tree_node* tree) 
{

	for (tree_node* node : tree->nodes) 
	{
		destroyTree(node);
		delete node;
	}

}



void Tree::printAsBranch(tree_node* node, std::string const& prefix, bool root, bool last)
{

	std::cout << prefix << (root ? "" : (last ? "\\-" : "|-")) << (node ? node->data : "") << std::endl;
	if (!node || node->nodes.size() == 0)
		return;
	std::vector<tree_node*> &vector = node->nodes;
	for (size_t i = 0; i < vector.size(); ++i)
		printAsBranch(vector[i], prefix + (root ? "" : (last ? "  " : "| ")), false, i + 1 >= vector.size());

}

void Tree::print(void)
{
	printAsBranch(head);
}


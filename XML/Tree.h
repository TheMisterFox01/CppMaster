#pragma once
#include <iostream>
#include <vector>

typedef struct tree_node {
	std::string data;
	tree_node* parent = NULL;
	std::vector<tree_node*> nodes;
}tree_node;

class Tree
{
protected:
	tree_node* head;

public:
	Tree();
	~Tree();

private:
	void printAsBranch(tree_node* node, std::string const& prefix = "", bool root = true, bool last = true);
public:
	void print(void);
};
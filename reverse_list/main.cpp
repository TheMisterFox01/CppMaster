#include "ReverseList.h"
#include <iostream>

int main(void) 
{
	ReverseList<int> r;
	
	r.pushBack(1);
	r.popBack(2);
	r.pushFront(3);
	r.popFront(1);
	r.pushBack(2);

	r.print();
	r.reverse();
	r.print();
	r.reverse();
	r.print();

	return 0;
}
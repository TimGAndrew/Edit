#ifndef NODE_H
#define NODE_H

#include <string>

using namespace std;

class Node
{
public:
	//Variables to hold data ? what data? the next node 
	//EDIT: int data;
	string data;
	Node *next;

	Node();
};

#endif

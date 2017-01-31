/*
	LinkedList.h

	Tim Andrew
	Jan 26th, 2016
	PROG2400-701 - Assignment #1
	INSTRUCTOR: Hal O'Connell
*/
#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <string>
#include <iostream>

using namespace std;


//A struct node to handle the information being stored:
struct Node
{
	//String to hold a line of text:
	string line;
	//Pointer to the next node:
	Node* next;
};

class LinkedList
{
private:
	Node* head;
	

public:
	int listLength;
		//Constructor initialized Linked List
	LinkedList();
		//Destructor clears memory used by the list.
	~LinkedList();
		
		//Insert a line at (places line before):
	void Insert(string line, int position);
		//Substitute line at:
	void Substitute(string line, int position);
		//Delete line at (optional: range):
	void Delete(int position, int endPosition = 0);
		//View  at (optional: List lines or range):
	void View(int position = 0, int endPosition = 0);

		//overridden << operator for file output:
	friend ostream& operator<<(ostream& output, LinkedList& list);
};

#endif
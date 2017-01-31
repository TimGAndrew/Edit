/*
	LinkedList.cpp

	Tim Andrew
	Jan 26th, 2016
	PROG2400-701 - Assignment #1
	INSTRUCTOR: Hal O'Connell
*/
#include "LinkedList.h"

	//Constructor sets the node up
LinkedList::LinkedList() {
	head = new Node;
	head->line = "HEAD NODE";
	head->next = NULL;
	listLength = 0;
}

	//Destructor de-allocates memory used by the list.
LinkedList::~LinkedList()
{
	Node* p = head;
	Node* q = head;
	while (listLength >=0)
	{
		p = q;
		q = p->next;
		delete p;
		--listLength;
	}
}

	//Insert a line at (places line before):
void LinkedList::Insert(string line, int position)
{
		//Create a new node:
	Node* newNode = new Node;
		//Set the newNode's line variable to incoming line data:
	newNode->line = line;

		//determine if the position is within range:
	if (position <= 0 || position > listLength+1)
	{
		system("cls");
		cout << "\t[LINE OUT OF RANGE]" << endl;
		return;
	}
		//if there is no next node:
	if (!head->next)
	{
			//set the newNode to this node:
		head->next = newNode;
			//Increment listLength:
		++listLength;
		system("cls");
		cout << "\t[LINE " << position << " ADDED]" << endl;
		return;
	}

		//If the line hasnt been handled by here, we need to traverse:
		//so first set up counters and 2 pointers:
	int count = 0;
	Node* p = head;
	Node* q = head;

		//while q is not Null:
	while (q)
	{
		if (count == position)
		{
				//set p's next to newNode pointer
			p->next = newNode;
				//
			newNode->next = q;
			++listLength;
			system("cls");
			cout << "\t[LINE " << position << " ADDED]" << endl;
			return;
		}
		p = q;
		q = p->next;
		++count;
	}

		//at this point q is null and we are on the last list item:
	if (count == position)
	{
		p->next = newNode;
		newNode->next = q;
		++listLength;
		system("cls");
		cout << "\t[LINE " << position << " ADDED]" << endl;
		return;
	}
		//at this point something went wrong:
	system("cls");
	cout << "\t[LINE COULD NOT BE ADDED]" << endl;
	return;
}

	//Substitute line at :
void LinkedList::Substitute(string line, int position)
{
	if (position <= 0 || position > listLength)
	{
		system("cls");
		cout << "\t[INVALID LINE ENTERED]" << endl;
		return;
	}

	Node* p = head;
	Node* q = head;

	q = p->next;

	//set up a variable for the line number:
	int lineNumber = 1;

		//Find the position in the list
	while (lineNumber != position)
	{
		p = q;
		q = p->next;
		++lineNumber;
	}
		//update the line:
	q->line = line;
	system("cls");
	cout << "\t[LINE " << position << " SUBSTITUTED]" << endl;

}

	//Delete line at (optional: range):
void LinkedList::Delete(int position, int endPosition)
{
	Node* p = head;
	Node* q = head;

	q = p->next;

	//set up a variable to display the line number:
	int lineNumber = 1;

	//Delete has no range:
	if (endPosition == 0)
	{

		//First check if position is a valid positions:
		if (position <= 0 || position > listLength)
		{
			system("cls");
			cout << "\t[INVALID LINE ENTERED]" << endl;
			return;
		}

		//find position:
		while (lineNumber != position)
		{
			p = q;
			q = p->next;
			++lineNumber;
		}

		p->next = q->next;
		delete q;
		listLength--;
		system("cls");
		cout << "\t[LINE " << position << " DELETED]" << endl;
		return;
	}
	//Delete has a range:
	else
	{
		//First check if endposition is a valid positions:
		if (endPosition <= 0 || endPosition > listLength)
		{
			system("cls");
			cout << "\t[INVALID LINE ENTERED]" << endl;
			return;
		}

		//find start position:
		while (lineNumber != position)
		{
			p = q;
			q = p->next;
			++lineNumber;
		}

		for (int i = endPosition; i >= position; --i)
		{
			this->Delete(i);
		}
		system("cls");
		cout << "\t[LINES " << position << " to " << endPosition << " DELETED]" << endl;
		return;
	}

}

	//View at (optional: List lines or range):
void LinkedList::View(int position, int endPosition)
{
	Node* p = head;
	Node* q = head;

	q = p->next;

		//set up a variable to display the line number:
	int lineNumber = 1;

		//View is run:
	if (position == 0 && endPosition == 0)
	{
			//make output look nice (with #'s and a pipe):
		while (lineNumber <= listLength)
		{
			p = q;
				//output line #:
			cout << lineNumber;

				//determine # to make output look nice:
			if (lineNumber < 10)
			{
				cout << "   ";
			}
			else if (lineNumber < 100)
			{
				cout << "  ";
			}
			else
			{
				cout << " ";
			}
			cout << "| " << p->line << endl;

				//go to next node:
			q = p->next;
			++lineNumber;
		}
	}
		//List line # is run:
	else if (endPosition == 0)
	{
		//First check if optional positions are valid positions:
		if (position <= 0 || position > listLength)
		{
			system("cls");
			cout << "\t[INVALID LINE ENTERED]" << endl;;
			return;
		}

			//find the line:
		while (lineNumber != position)
		{
			p = q;
			q = p->next;
			++lineNumber;
		}

		p = q;
			//then print the line #
		cout << lineNumber;

			//determine # to make output look nice:
		if (lineNumber < 10)
		{
			cout << "   ";
		}
		else if (lineNumber < 100)
		{
			cout << "  ";
		}
		else
		{
			cout << " ";
		}
		cout << "| " << p->line << endl;
	}
		//List Line Range is run:
	else
	{
			//First check if optional positions are valid positions:
		if (position <= 0 || position > listLength || endPosition <= 0 || endPosition > listLength)
		{
			system("cls");
			cout << "\t[INVALID LINE ENTERED]" << endl;
			return;
		}

			//find the first line:
		while (lineNumber != position)
		{
			p = q;
			q = p->next;
			++lineNumber;
		}
			//print out each line until range is hit:
		while (lineNumber <= endPosition)
		{
			p = q;
			//output line #:
			cout << lineNumber;

			//determine # to make output look nice:
			if (lineNumber < 10)
			{
				cout << "   ";
			}
			else if (lineNumber < 100)
			{
				cout << "  ";
			}
			else
			{
				cout << " ";
			}
			cout << "| " << p->line << endl;

			//go to next node:
			q = p->next;
			++lineNumber;
		}
	}
}

	//handles the printout of the linked list (used to output to file)
ostream& operator<<(ostream& output, LinkedList& list)
{
		//get the current head node:
	Node* currNode = list.head;
	currNode = currNode->next;
	int linecount = 1;

		//While the current node is not null:
	while (linecount <= list.listLength)
	{
			//send the line to the output:
		output << currNode->line << endl;
			//move to the next node:
		currNode = currNode->next;
		++linecount;
	}
		//return the output:
	return output;
}


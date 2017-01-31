/*
	Main.cpp

	Tim Andrew
	Jan 26th, 2016
	PROG2400-701 - Assignment #1
	INSTRUCTOR: Hal O'Connell
*/

//FUNCTIONS:
/*
DONE: Keep the entire text on a linked list, one line in a separate node.
DONE: You may not use the classes provided in the STL to implement the list. You may use strings (string.h, not the string class).
DONE: You may use regular expressions to parse command line input.
DONE: Start the program with entering EDIT <input file> <output file>, after which a prompt appears along with the line number.
DONE: If the letter I is entered with a number n following it, then insert the text to be followed before line n.
DONE: If I is not followed by a number, then insert the text before the current line.
DONE: If D is entered with two numbers n and m, one n, or no number following it, then delete lines n through m, line n, or the current line.
DONE: If V is entered display the entire set of lines in the buffer
DONE: G followed by a number, n, goes to line n in the buffer.
DONE: If there is no line number it goes to the first line of the buffer.
DONE: L lists the lines of the buffer using the same numbering system as the D command.
DONE: S Substitutes a new line, entered by the user, for the current line in the buffer, or at a specified line number.
DONE: The command must prompt the user for the new line, perform the replacement, and then automatically issue the V command
		to list the buffer contents.
DONE: E signifies exit and saving the text in the second file in the argument list.
DONE:  Q signifies exit immediately without saving changes.
*/
//RUBRIC:
/*
DONE: Edit opens a new or existing file
DONE: Lines are added to the file
DONE: Exit creates the output file specified as an argument and all data is correct.
DONE: If the file exists it overwrites the old file.
DONE: Quit works as expected

DONE: Insert functions without errors through full range of expected function.
DONE: Insert handles invalid line numbers
DONE: Code is error free

DONE: Delete functions without errors through full range of expected function.
DONE: Delete handles invalid line numbers
DONE: Code is error free

DONE: List/View functions without errors through full range of expected function.
DONE: List handles invalid line numbers
DONE: Code is error free

DONE: Substitute functions without errors through full range of expected function.
DONE: Substitute handles invalid line numbers
DONE: Code is error free

*/

#include <conio.h>
#include <fstream>
#include <regex>
#include "LinkedList.h"


void DisplayHelp(LinkedList& list)
{
	//clear the screen:
	system("cls");
	cout << "HELP:" << endl;
	cout << "-------------------------------------------------" << endl;
	cout << "\tINSERT:" << endl;
	cout << "\t\tI\t=\tInsert text before current line" << endl;
	cout << "\t\tI #\t=\tInsert text before line #" << endl;
	cout << "\tDELETE:" << endl;
	cout << "\t\tD\t=\tDelete current line" << endl;
	cout << "\t\tD #\t=\tDelete line #" << endl;
	cout << "\t\tD # #\t=\tDelete lines # through #" << endl;
	cout << "\tVIEW:" << endl;
	cout << "\t\tV\t=\tDisplay all lines" << endl;
	cout << "\tGOTO:" << endl;
	cout << "\t\tG\t=\tGo to first line" << endl;
	cout << "\t\tG #\t=\tGo to line #" << endl;
	cout << "\tLIST:" << endl;
	cout << "\t\tL\t=\tList current line" << endl;
	cout << "\t\tL #\t=\tList line #" << endl;
	cout << "\t\tL # #\t=\tList lines # through #" << endl;
	cout << "\tSUBSTITUTE:" << endl;
	cout << "\t\tS\t=\tSubstitute current line with new line" << endl;
	cout << "\t\tS #\t=\tSubstitute line # with new line" << endl;
	cout << "\tHELP:" << endl;
	cout << "\t\tH\t=\tDisplays this help screen" << endl;
	cout << "\tEXIT:" << endl;
	cout << "\t\tE\t=\tExists immediately saving the text to the output.file" << endl;
	cout << "\tQUIT:" << endl;
	cout << "\t\tQ\t=\tQuits immediately without saving" << endl;
	cout << "-------------------------------------------------" << endl;
	cout << "Press Any Key to Return";
	_getch();
	system("cls");


	//Begin output to screen:
	cout << "EDIT - (enter 'H' for help)" << endl;

	//show the list:
	list.View();


}

int GetNumber(int whichNumber, string command, int currentLine)
{
	string num = "";
	int spaces = 0;

	//Loop through each char in the command:
	for (char& c : command)
	{
		if (c == ' ')
			++spaces;
		else if (whichNumber == 1 && spaces <= 1 && isdigit(c))
			num += c;
		else if (whichNumber == 2 && spaces == 2 && isdigit(c))
			num += c;
	}
	if (num == "")
		return currentLine;
	else
		return stoi(num);
}

void RunCommand(string command, int currentLine, LinkedList& list)
{

	//Regex search strings:
	//INSERT:
	regex cmdI("[I,i]");
	regex cmdIn("[I,i] [0-9]+");
	//DELETE:
	regex cmdD("[D,d]");
	regex cmdDn("[D,d] [0-9]+");
	regex cmdDnn("[D,d] [0-9]+ [0-9]+");
	//VIEW:
	regex cmdV("[V,v]");
	//GOTO:
	regex cmdG("[G,g]");
	regex cmdGn("[G,g] [0-9]+");
	//LIST:
	regex cmdL("[L,l]");
	regex cmdLn("[L,l] [0-9]+");
	regex cmdLnn("[L,l] [0-9]+ [0-9]+");
	//SUBSTITUTE:
	regex cmdS("[S,s]");
	regex cmdSn("[S,s] [0-9]+");
	//HELP:
	regex cmdH("[H,h]");

	//insert:
	if (regex_match(command, cmdIn))
	{
		int num = GetNumber(1, command,currentLine);
		string inputString;
		cout << "Text to insert at line " << num << " > ";
		getline(cin, inputString);
		list.Insert(inputString, num);
		//Begin output to screen:
		cout << "EDIT - (enter 'H' for help)" << endl;

		//show the list:
		list.View();
	}
	else if (regex_match(command, cmdI))
	{
		string inputString;
		cout << "Text to insert at line " << currentLine << " > ";
		getline(cin, inputString);
		list.Insert(inputString, currentLine);
		//Begin output to screen:
		cout << "EDIT - (enter 'H' for help)" << endl;

		//show the list:
		list.View();
	}
	else if (regex_match(command, cmdDnn))
	{
		//delete range:
		int number1 = GetNumber(1, command, currentLine);
		int number2 = GetNumber(2, command, currentLine);
		list.Delete(number1, number2);
		//Begin output to screen:
		cout << "EDIT - (enter 'H' for help)" << endl;

		//show the list:
		list.View();
	}
	else if (regex_match(command, cmdDn))
	{
		//delete number:
		int number = GetNumber(1, command, currentLine);
		list.Delete(number);
		//Begin output to screen:
		cout << "EDIT - (enter 'H' for help)" << endl;

		//show the list:
		list.View();
	}
	else if (regex_match(command, cmdD))
	{	//Delete node:
		list.Delete(currentLine);
		//Begin output to screen:
		cout << "EDIT - (enter 'H' for help)" << endl;

		//show the list:
		list.View();
	}
	else if (regex_match(command, cmdV))
	{
		//view list:
		system("cls");
		//Begin output to screen:
		cout << "EDIT - (enter 'H' for help)" << endl;

		//show the list:
		list.View();
	}
	else if (regex_match(command, cmdSn))
	{
		int num = GetNumber(1, command, currentLine);
		string inputString;
		cout << "Text to substitute at line " << num << " > ";
		getline(cin, inputString);
		list.Substitute(inputString, num);
		//Begin output to screen:
		cout << "EDIT - (enter 'H' for help)" << endl;

		//show the list:
		list.View();
	}
	else if (regex_match(command, cmdS))
	{
		string inputString;
		cout << "Text to substitute at line " << currentLine << " > ";
		getline(cin, inputString);
		list.Substitute(inputString, currentLine);
		//Begin output to screen:
		cout << "EDIT - (enter 'H' for help)" << endl;

		//show the list:
		list.View();
	}
	else if (regex_match(command, cmdLnn))
	{
		int number1 = GetNumber(1, command, currentLine);
		int number2 = GetNumber(2, command, currentLine);
		//Begin output to screen:
		system("cls");
		cout << "EDIT - (enter 'H' for help)" << endl;

		list.View(number1, number2);
	}
	else if (regex_match(command, cmdLn))
	{
		int num = GetNumber(1, command, currentLine);
		//Begin output to screen:
		system("cls");
		cout << "EDIT - (enter 'H' for help)" << endl;

		list.View(num);
	}
	else if (regex_match(command, cmdL))
	{
		//Begin output to screen:
		system("cls");
		cout << "EDIT - (enter 'H' for help)" << endl;

		list.View(currentLine);
	}
	else
	{
		system("cls");
		cout << "\t[INVALID COMMAND]" << endl;
		//Begin output to screen:
		cout << "EDIT - (enter 'H' for help)" << endl;

		//show the list:
		list.View();
	}
		
}


//Main entry point of the program:
//Requires 2 arguments, input file and output file, as an argument vector from command line.
int main(int argc, char* argv[])
{
		//Set up variables to hold argument file names
	string inputFile;
	string outputFile;

		//set up a variable to hold the current line:
	int currentLine = 1;
	
	//If there are 2 command line arguents, set up file variables:
	if (argc == 3)
	{
		inputFile = argv[1];
		outputFile = argv[2];

		//TODO: check if these are valid names (regex??) (file handler class??)
	}
	//if not, exit:
	else
	{
		cout << " Usage:  EDIT input.file output.file" << endl;
		return 0;
	}

	//Create a linked list:
	LinkedList list;


	//set up an input file stream:
	ifstream inFile(inputFile);

	//Check if input stream exists:
	if (inFile)
	{
		//Create a string to hold each line and a line counter:
		string fileLine;
		int lineCounter = 1;

		//Go through the file and get each line:
		while (getline(inFile, fileLine))
		{
			//Add current line to the list:
			list.Insert(fileLine, lineCounter);

			++lineCounter;
		}
	}

		//Set up a boolean to handle the program run:
	bool editLoop = true;
	system("cls");

	//Begin output to screen:
	cout << "EDIT - (enter 'H' for help)" << endl;

	//show the list:
	list.View();

		//enter the main loop of the edit program:
	while (editLoop)
	{

			//set up a command string:
		string command;

		//Display current line and ask for the command:
		cout << "CURRENT LINE [" << currentLine << "]\n" << "COMMAND > " << flush;
		getline(cin, command);

		//pre-handle Commands:
		regex cmdGn("[G,g] [0-9]+");
		regex cmdG("[G,g]");

		if (command == "q" || command == "Q")
		{
			editLoop = false;
		}
		else if (regex_match(command, cmdG))
		{
			system("cls");
			currentLine = 1;
			//Begin output to screen:
			cout << "EDIT - (enter 'H' for help)" << endl;

			//show the list:
			list.View();
		}
		else if (regex_match(command, cmdGn))
		{
			system("cls");
			int number = GetNumber(1, command, currentLine);
			if (number > 0 && number <= list.listLength)
				currentLine = number;
			else
				cout << "\t[INVALID LINE NUMBER]" << endl;
			//Begin output to screen:
			cout << "EDIT - (enter 'H' for help)" << endl;

			//show the list:
			list.View();
		}
		else if (command == "e" || command == "E")
		{
			editLoop = false;

			ofstream outFile;
			outFile.open(outputFile);
			outFile << list;
			outFile.close();

		}
		else if (command == "h" || command == "H")
		{
			DisplayHelp(list);
		}
		else
		{
			RunCommand(command, currentLine, list);
		}
	}

	cout << "Exited Edit" << endl;
	return 0;
}
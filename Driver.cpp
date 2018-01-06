// Class implementation file: LinkedList.cpp //
#include "LinkedList.h"
#include <cassert>
#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>
using namespace std;

char getSelection();
void loadData(LinkedList &myList);
void insertElement(LinkedList &myList);
void removeElement(LinkedList &myList);
void shiftUp(LinkedList &myList);
void shiftDown(LinkedList &myList);
void deleteTheList(LinkedList &myList);
int getLocation(int min, int max);

void main()
{
	LinkedList myList, list2;
	int choice;
	do
	{
		cout << myList << endl;
		choice = getSelection();
		switch (choice)
		{
		case '1': loadData(myList); break;
		case '2': insertElement(myList); break;
		case '3': removeElement(myList); break;
		case '4': shiftUp(myList); break;
		case '5': shiftDown(myList); break;
		case '6': deleteTheList(myList); break;
		}
	} while ((choice != 'q') && (choice != 'Q'));
	cout << "\n\n    Goodbye.\n\n";
	system("pause");
}

void shiftDown(LinkedList &myList)
{
	int position;
	if (myList.size() <= 1)
		return;
	if (myList.size() != 2)
		position = getLocation(1, myList.size() - 1);
	else
		position = 1;
	myList.shiftElementDown(position);
}

void shiftUp(LinkedList &myList)
{
	int position;
	if (myList.size() <= 1)
		return;
	if (myList.size() != 2)
		position = getLocation(2, myList.size());
	else
		position = 2;
	myList.shiftElementUp(position);
}

void removeElement(LinkedList &myList)
{
	int position;
	if (myList.size() == 0)
		return;
	if (myList.size() != 1)
		position = getLocation(1, myList.size());
	else
		position = 1;
	myList.remove(position);
}

void deleteTheList(LinkedList &myList)
{
	myList.deleteList();
}

void insertElement(LinkedList &myList)
{
	int location;
	string element;
	if (myList.size() != 0)
		location = getLocation(1, myList.size() + 1);
	else
		location = 1;
	cout << "Enter a one-word element for the list: ";
	cin >> element;
	myList.insert(location, element);
}

void loadData(LinkedList &myList)
{
	ifstream infile;
	string filename;
	cout << "Please enter the file's name: ";
	cin >> filename;
	infile.open(filename.c_str());
	while (infile.fail())
	{
		infile.close();
		infile.clear();
		cout << "That is not a valid file name, please try again: ";
		cin >> filename;
		infile.open(filename.c_str());
	}
	myList.addNodesFromFile(infile);
}

char getSelection()
{
	char sel;
	do
	{
		cout << "Choose an option:\n";
		cout << "1) Add data from a file.\n";
		cout << "2) Insert an element.\n";
		cout << "3) Remove an element.\n";
		cout << "4) Shift an element up.\n";
		cout << "5) Shift an element down.\n";
		cout << "6) Delete the list.\n";
		cout << "Q) Quit.\n";
		cin >> sel;
		sel = toupper(sel);
		if ((!((sel >= '1') && (sel <= '6'))) && (sel != 'Q'))
		{
			cout << "That is not a listed option, please try again.\n";
		}
	} while ((!((sel >= '1') && (sel <= '6'))) && (sel != 'Q'));
	return sel;
}

int getLocation(int min, int max)
{
	int loc;
	assert(min < max);
	cout << "Enter a location int the range " << min << " to " << max << ": ";
	cin >> loc;
	while ((loc < min) || (loc > max))
	{
		cout << loc << " is not in the proper range.\n";
		cout << "Enter a location int the range " << min << " to " << max << ": ";
		cin >> loc;
	}
	return loc;
}

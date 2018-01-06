// Class implementation file: LinkedList.cpp //
// Name: Sean Mathews
// Date Modified: 11/28/17
// Class: CS-240
//Instructor: Klein
#include "LinkedList.h"
#include <assert.h>
#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>
using namespace std;

// The default constructor merely sets up an empty LinkedList. //
LinkedList::LinkedList()
{
	head = nullptr;
}
// The copy constructor makes a deep copy of the parameterized LinkedList. //
LinkedList::LinkedList(const LinkedList &list)
{
	nodePtr currPtr, thisCurrPtr, thisPrevPtr;
	if (list.head == nullptr)
		head = nullptr;
	else
	{
		head = getNode(list.head->item);
		thisPrevPtr = head;
		currPtr = list.head->next;
		while (currPtr != nullptr)
		{
			thisCurrPtr = getNode(currPtr->item);
			thisPrevPtr->next = thisCurrPtr;
			thisPrevPtr = thisCurrPtr;
			currPtr = currPtr->next;
		}
	}
}
// = operator
// The assignment operator makes the current
// object a copy of the parameterized object 
LinkedList& LinkedList::operator = (const LinkedList &list)
{
	if (head == list.head)
		return *this;
	deleteList();
	nodePtr currPtr, thisCurrPtr, thisPrevPtr;
	if (list.head == nullptr)
		head = nullptr;
	else
	{
		head = getNode(list.head->item);
		thisPrevPtr = head;
		currPtr = list.head->next;
		while (currPtr != nullptr)
		{
			thisCurrPtr = getNode(currPtr->item);
			thisPrevPtr->next = thisCurrPtr;
			thisPrevPtr = thisCurrPtr;
			currPtr = currPtr->next;
		}
	}
	return *this;
}

// The destructor systematically deletes //
// every node in the LinkedList.         //
LinkedList::~LinkedList()
{
	nodePtr currPtr;
	while (head != nullptr)
	{
		currPtr = head;
		head = head->next;
		currPtr->next = nullptr;
		delete currPtr;
	}
}

// The size member function returns the //
// number of nodes in the LinkedList.   //
int LinkedList::size() const
{
	int count = 0;
	nodePtr currPtr = head;
	while (currPtr != nullptr)
	{
		currPtr = currPtr->next;
		count++;
	}
	return count;
}
// The insert member function creates a new    //
// node containing the parameterized value,    //
// inserting it at the head of the LinkedList. //
// A boolean value indicating whether the      //
// insertion worked is returned.               //
bool LinkedList::insert(elementType elt)
{
	nodePtr insertPtr = getNode(elt);
	if (insertPtr == nullptr)
		return false;
	if (head == nullptr)
		head = insertPtr;
	else
	{
		insertPtr->next = head;
		head = insertPtr;
	}
	return true;
}
// The remove member function locates the first occurrence of the parameterized //
// value in the LinkedList and detaches it from the LinkedList.  A boolean      //
// value indicating whether the removal worked is returned.                     //
bool LinkedList::remove(elementType elt)
{
	nodePtr currPtr = head;
	nodePtr prevPtr = nullptr;
	bool foundIt = false;
	while ((!foundIt) && (currPtr != nullptr))
	{
		if (currPtr->item == elt)
			foundIt = true;
		else
		{
			prevPtr = currPtr;
			currPtr = currPtr->next;
		}
	}
	if (foundIt)
	{
		if (prevPtr == nullptr)
			head = currPtr->next;
		else
			prevPtr->next = currPtr->next;
		delete currPtr;
	}
	return foundIt;
}
// The retrieve member function locates the first occurrence of the parameterized  //
// value in the LinkedList and sets the parameterized nodePtr to its memory        //
// location.  A boolean value indicating whether the retrieval worked is returned. //
bool LinkedList::retrieve(elementType elt, int &position)
{
	bool foundIt = false;
	nodePtr currPtr = head;
	position = 0;
	while ((!foundIt) && (currPtr != nullptr))
	{
		position++;
		if (currPtr->item == elt)
			foundIt = true;
		else
			currPtr = currPtr->next;
	}
	return foundIt;
}

// The input operator reads all values of type          //
// elementType from the parameterized input stream,     //
// inserting them into the parameterized LinkedList,    //
// until the input stream has been completely depleted. //
istream& operator >> (istream &sourceFile, LinkedList &list)
{
	elementType nextElt;
	sourceFile >> nextElt;
	while (!sourceFile.eof())
	{
		list.insert(nextElt);
		sourceFile >> nextElt;
	}
	return sourceFile;
}


// The output operator outputs the values in the LinkedList, //
// each on a separate output line in the parameterized       //
// output stream, starting with the head element.            //
ostream& operator << (ostream &destFile, const LinkedList &list)
{
	//nodePtr ptr;
	list.displayList(destFile);
	return destFile;
}
// The getNode member function creates and returns //
// a new nodePtr, pointing to a node with the      //
// parameterized value as its item member and with //
// NULL as the value of its next member.           //
nodePtr LinkedList::getNode(elementType elt)
{
	nodePtr temp = new node;
	if (temp != nullptr)
	{
		temp->item = elt;
		temp->next = nullptr;
	}
	return temp;
}

bool LinkedList::addNodesFromFile(ifstream &infile)
{
	elementType newItem;//data gonna be read in
	nodePtr nodeMaker = nullptr;//nodemaker is the ptr that makes the nodes, and keeps repointing at the nodes being made, losing the old nodes everytime
	nodePtr nodeTracker = nullptr;//nodeTracker is the ptr that keeps pointing at the nodes that were made so we dont lose track of those nodes

	//nodeMaker = this->head; //this points temp at head

		infile >> newItem;//reads in data from file
		nodeMaker = getNode(newItem);//makes the node called temp, then puts the data(newitem) into the node with the next ptr
		head = nodeMaker; //assigns head ptr to temp ptr
		nodeTracker = head;
	
		while (infile.good()) {

			infile >> newItem;//reads in data from file
			nodeMaker = getNode(newItem);//makes the node called temp, then puts the data(newitem) into the node with the next ptr
			nodeTracker->next = nodeMaker;//connects the previous node's next
			nodeTracker = nodeMaker;//connects 
		}
	return true;
}

void LinkedList::displayList(ostream &outs) const
{
	nodePtr displayPtr = head;//need to set displayptr = to head first to get started with printing
	//need a temp Node and temp->next


	int numNodes = 1; //for the numbering in the list

	//use this-> to reference the list pointer
	outs << "List size: " << this->size() << " nodes." << endl
		<< "Position:      " << "Value:      " << endl
		<< "----------------------------" << endl;
		 
	//display the contents of each node one by one using a loop
	if (this->size() == 0) {
		outs << "List is empty";
	}
		else {
			//since we know that the list has ATLEAST 1 node since passed the if, then print the first node outside of the loop
				//while the next pointer isnt nullptr, display outs
					//print head node out of while

			outs << "       " << numNodes << "	" << displayPtr->item << endl;
			displayPtr = head->next;
			//displayPtr->next is the green shit
			while (displayPtr->next != nullptr) {
				//print the head node
				//then set displayptr to head->next 
				numNodes += 1;
				outs << "       " << numNodes << "	" << displayPtr->item << endl;
				displayPtr = displayPtr->next;
			}
		}

	return;
}

void LinkedList::deleteList()
{
	nodePtr currPtr;
	while (head != nullptr)
	{
		currPtr = head;
		head = head->next;
		currPtr->next = nullptr;
		delete currPtr;
	}
}

bool LinkedList::insert(int position, elementType elt)
{
	nodePtr curPtr = head;
	nodePtr newNode = getNode(elt);
	if ((position < 1) || position >(size() + 1))
		return false;
	if (head == nullptr)
		head = newNode;
	else if (position == 1)
	{
		newNode->next = head;
		head = newNode;
	}
	else
	{
		for (int i = 1; i < position - 1; i++)
		{
			curPtr = curPtr->next;
		}
		newNode->next = curPtr->next;
		curPtr->next = newNode;
	}
	return true;
}

bool LinkedList::shiftElementDown(int position)
{
	
	
	nodePtr curPtr = head;
	nodePtr beforeCurPtr = head;
	nodePtr afterCurPtr = head; //all of these ptrs are pointing at the head, but will end up at different positions to perform 
								//to perform the shifting operation

	nodePtr safetyPtr = head;			//to not lose data;
	if (position == 1) {

		for (int i = 1; i < position; i++) {
			curPtr = curPtr->next;				//this points at the position node
		}

		for (int i = 1; i < position + 1; i++)
		{
			afterCurPtr = afterCurPtr->next;			//this should be pointing to the node after curPtr
		}

		for (int i = 1; i < position + 2; i++)
		{
			safetyPtr = safetyPtr->next;			//this should be pointing to the node after, afterCurPtr
		}

		//curPtr = curPtr->next;
		curPtr->next = safetyPtr;
		afterCurPtr->next = head;
		head = afterCurPtr;
		
		
		//afterCurPtr->next = curPtr;
		
		

		return true;

	}
		
	else {
		//This is the node pointer thing to keep itterating until we get to the node we want//
		for (int i = 1; i < position; i++) {
			curPtr = curPtr->next;				//this points at the position node
		}

		for (int i = 1; i < position - 1; i++)
		{										//this points at the node before position
			beforeCurPtr = beforeCurPtr->next;
		}

		for (int i = 1; i < position + 1; i++)
		{
			afterCurPtr = afterCurPtr->next;			//this points at the node after position
		}

		for (int i = 1; i < position + 2; i++)
		{
			safetyPtr = safetyPtr->next;			//this points at the node after position
		}

		if (position >= this->size()) {
			return false;
		}
		if (position < 1) {
			return false;
		}
		else {
			
			beforeCurPtr->next = afterCurPtr;//this takes the beforeCurPtr's next, which is what we want, to point at the node what aftercurptr is pointing at, use a picture
			afterCurPtr->next = curPtr; // this points afterCurPtr's next to curPtr 
			curPtr->next = safetyPtr;

		}

	}

	return true;
}

bool LinkedList::shiftElementUp(int position)
{
	nodePtr curPtr = head;
	nodePtr beforeCurPtr = head;
	nodePtr afterCurPtr = head; //all of these ptrs are pointing at the head, but will end up at different positions to perform 
								//to perform the shifting operation

	nodePtr safetyPtr = head;			//to not lose data;

	//This is the node pointer thing to keep itterating until we get to the node we want//
	if (position == 2) {
		for (int i = 1; i < position; i++) {
			curPtr = curPtr->next;				//this points at the position node
		}

		for (int i = 1; i < position - 1; i++)
		{
			beforeCurPtr = beforeCurPtr->next;			//this should be pointing to the node after curPtr
		}

		for (int i = 1; i < position + 1; i++)
		{
			safetyPtr = safetyPtr->next;			//this should be pointing to the node after, afterCurPtr
		}



		curPtr->next = beforeCurPtr;
		beforeCurPtr->next = safetyPtr;
		head = curPtr;

		return true;

	}

	else {


		for (int i = 1; i < position; i++) {
			curPtr = curPtr->next;				//this points at the position node
		}

		for (int i = 1; i < position - 1; i++)
		{										//this points at the node before position
			beforeCurPtr = beforeCurPtr->next;
		}

		for (int i = 1; i < position + 1; i++)
		{
			afterCurPtr = afterCurPtr->next;			//this points at the node after position
		}

		for (int i = 1; i < position - 2; i++)
		{
			safetyPtr = safetyPtr->next;			//this points at the node after position
		}

	



	safetyPtr->next = curPtr;
	curPtr->next = beforeCurPtr;
	beforeCurPtr->next = afterCurPtr;
}
	return true;
}

bool LinkedList::remove(int position)
{
	nodePtr currPtr = head;
	nodePtr prevPtr = nullptr;
	if ((position < 1) || position > size())
		return false;
	if (position == 1)
	{
		head = head->next;
		delete currPtr;
	}
	else
	{
		for (int i = 1; i < position; i++)
		{
			prevPtr = currPtr;
			currPtr = currPtr->next;
		}
		prevPtr->next = currPtr->next;
		delete currPtr;
	}
	return true;
}
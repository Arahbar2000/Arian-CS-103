#include <iostream>
#include "mlist.h"
using namespace std;
//------------------------------------------------------------------------------
//IMPORTANT: You are not allowed to remove or add any parameters to any functions.
//NOTE: There can only be at most 2 loops in this file
//------------------------------------------------------------------------------

//Constructor, construct an empty doubly linked list.
MList::MList(){
	ntop = NULL;
	nbottom = NULL;
}

//Destructor, properly clears and deallocates everything of current list.
//simply call the clear function if you have already implemented that.
MList::~MList(){
    clear();
}

//Note: RECURSION --- This function should be implemented using recursion.
//this function properly clears and deallocates everything of current list.
//there should be no loop in this function
void MList::clear(){
	if(ntop != NULL)
	{
		pop_top();
		clear();
	}
}

//returns a boolean true if the list is empty, false if otherwise.
bool MList::isEmpty(){
if(ntop == NULL)
{
	return true;
}
else
{
	return false;
}

}

/*
	Add or insert a new node with d_item as its data at the top of the list.
	You need to dynamically allocate memory for the new node.
*/
void MList::push_top(Data* d_item){
	if(isEmpty())
	{
		nbottom = new Node;
		nbottom -> nodeData = d_item;
		nbottom -> next = NULL;
		nbottom -> prev = NULL;
		ntop = nbottom;
	}
	else
	{
		Node* temp = new Node;
		temp -> nodeData = d_item;
		temp -> next = ntop;
		temp -> prev = NULL;
		ntop -> prev = temp;
		ntop = temp;
	}

}

/*
	Add or insert a new node with d_item as its data at the bottom of the list.
	You need to dynamically allocate memory for the new node.
*/
void MList::push_bottom(Data* d_item){
	if(isEmpty())
	{
		ntop = new Node;
		ntop -> nodeData = d_item;
		ntop -> next = NULL;
		ntop -> prev = NULL;
		nbottom = ntop;
	}
	else
	{
		Node* temp = new Node;
		temp -> nodeData = d_item;
		temp -> prev = nbottom;
		temp -> next = NULL;
		nbottom -> next = temp;
		nbottom = temp;

	}
	
}

/*
	Delete or remove the top node of the list.
	Once pop, you need to properly deallocate the memory for the node (not the data).
	If your list is currently empty, you don't have to do anything.
*/
void MList::pop_top(){
	if(ntop != NULL)
	{
		Node* temp = ntop;
		if(ntop -> next != NULL)
		{
			ntop -> next -> prev = NULL;
			ntop = ntop -> next;
		}
		else
		{
			ntop = NULL;
			nbottom = NULL;
		}
		delete temp;
	}
}

/*
	Delete or remove the bottom node of the list.
	Once pop, you need to properly deallocate the memory for the node (not the data).
	If your list is currently empty, you don't have to do anything.
*/
void MList::pop_bottom(){
if(nbottom != NULL)
{
	Node* temp = nbottom;
	if(nbottom -> prev != NULL)
	{
		nbottom = nbottom -> prev;
		nbottom -> next = NULL;
	}
	else
	{
		ntop = NULL;
		nbottom = NULL;
	}
	delete temp;
}
    
    
    
}

/*
	Note: RECURSION --- This function should be implemented using recursion.
	Search a node in the list that has data with the same name as the parameter.
	If one is found, return the pointer to the node.
	If one is not found, return NULL.
*/
Node* MList::search(Node* start, string name){
	if(start == NULL)
	{
		return NULL;
	}
	else if(start -> nodeData -> name == name)
	{
		return start;
	}
	else
	{
		return search(start -> next, name);
	}
}

//Swapping node a with node b.
void MList::swapNode(Node* a, Node*b){
	Node* temp = a -> prev;
	//Node temp = a*;
	if(a != b)
	{
		removeNode(a);
		if(b -> prev == a)
		{
			insertAfter(a, b);
		}
		else
		{
			insertAfter(a, b -> prev);
		}
	    removeNode(b);
	    if(temp == b)
	    {
	    	insertAfter(b, a);
	    }
	    else
	    {
	    	insertAfter(b, temp);
	    }
	}
} 

/*
	This function PERMANENTLY deletes a node from the list given a pointer to that node.
	You can assume that the node exists in the list - no need to search for the node.
*/
void MList::deleteNode(Node* a){
	if(a -> prev == NULL)
	{
		ntop = ntop -> next;
	}
	else
	{
		a -> prev -> next = a -> next;
	}
	if(a -> next == NULL)
	{
		nbottom = nbottom -> prev;
	}
	else
	{
		a -> next -> prev = a -> prev;
	}
	delete a;
    
    

}

/*
	Unlike the delete function above, this function does NOT permanently delete the node.
	What you need to do at the last step is to set the node's prev and next pointers to NULL.
	Again, you can assume that the node exists in the list - no need to search for the node.
	Note: this function will be useful
        when we want to insert the given node later at another position after you remove it from the list.
*/
void MList::removeNode(Node* a){
	if(a -> prev == NULL)
	{
		ntop = ntop -> next;
		if(ntop != NULL)
		{
			ntop -> prev = NULL;
		}
	}
	else
	{
		a -> prev -> next = a -> next;
	}
	if(a -> next == NULL)
	{
		nbottom = nbottom -> prev;
		if(nbottom != NULL)
		{
			nbottom -> next = NULL;
		}
	}
	else
	{
		a -> next -> prev = a -> prev;
	}
	if(isEmpty())
	{
		ntop = NULL;
		nbottom = NULL;
	}
	a->next = NULL;
	a -> prev = NULL;
}

/*
	Insert node a after node b.
	Note: b can be NULL, Q: what does that mean?
    otherwise, you can assume that b exists in the list.
*/
void MList::insertAfter(Node *a, Node* b){
	if(b == NULL)
	{		
		if(isEmpty())
		{
			ntop = a;
			ntop -> next = NULL;
			ntop -> prev = NULL;
			nbottom = ntop;
		}
		else
		{
			a -> next = ntop;
			a -> prev = NULL;
			ntop -> prev = a;
			ntop = a;
		}
	}
	else
	{
		if(b -> next != NULL)
		{
			a -> next = b -> next;
			a -> next -> prev = a;
			a -> prev = b;
			b -> next = a;
		}
		else
		{
			a -> next = NULL;
			a -> prev = nbottom;
			b -> next = a;
			nbottom = a;
		}
	}


    
    
    
    
}


/*
	Note: RECURSION --- This function should be implemented using recursion.
	Implement a SELECTION SORT algorithm using recursion.
	The function takes in a start node.
	Things to keep in mind:
		1). sort should NOT be run if the list is empty.
		2). if mode = true, sort by name in alphabetical order
			(i.e., A-Za-z) based on ASCII number if mode = true
        3). if mode = false, sort by size in ascending order (low->high)
	You can search any online resources available to you (i.e. search 'selection sort')
	to understand the basic idea behind the selection sort algorithm.
    Note: 
        1). there can only be at most one loop in this function
        2). this function is private
            see sortByNameSelection and sortBySizeSelection for the calls to this function
*/
void MList::sortSelection(Node* start, bool mode){
	if(start != NULL)
	{
		Node* temp = start -> next;
		string first = start -> nodeData -> name;
		int min = (int)start -> nodeData -> size;
		Node* target = start;
		while(temp != NULL)
		{
			if(mode == true) //sort by name
			{
				if(temp -> nodeData -> name.compare(first) < 0)
				{
					target = temp;
					first = temp -> nodeData -> name;
				}
			}
			else //sort by size
			{


					if((int)temp -> nodeData -> size < min)
					{
						target = temp;
						min = (int)temp -> nodeData -> size;
					}
			}
			temp = temp -> next;
		}
		swapNode(target, start);
		sortSelection(target -> next, mode);
	}
}
    
    
    




/*
	Note: RECURSION --- This function should be implemented using recursion.
	Implement an INSERTION SORT algorithm using recursion.
	The function takes in a start node.
	Things to keep in mind:
		1). sort should NOT be run if the list is empty.
		2). we are trying to sort by name in alphabetical order
			(i.e., A-Za-z) based on ASCII number.
	You can search any online resources available to you (i.e. search 'insertion sort')
	to understand the basic idea behind the insertion sort algorithm.
	The gif from the wikipedia page of this algorithm is the easiest to understand in my opinion
	Link: https://en.wikipedia.org/wiki/Insertion_sort
    Note: 
        1). there can only be at most one loop in this function
        2). this function is private, see sortByNameInsertion for the call to this function
*/
void MList::sortInsertion(Node* start){
	if(start != NULL && start -> next != NULL)
	{
		Node* temp = start -> next;
		Node* input = start;
		int counter = 0;
		while(temp -> nodeData -> name.compare(start -> nodeData -> name) < 0)
		{
			counter++;
			swapNode(temp, start);
			if(counter == 1)
			{
				input = temp;
			}
			if(temp -> prev != NULL)
			{
				start = temp -> prev;
			}
		}
		sortInsertion(input -> next);
	}
    
    
    
    
    
    
}


/*
	Note: RECURSION --- This function should be implemented using recursion.
	Traverse and print our list from node n to the top.
	we will seperate each node printed by the passed-in delimiter.
	If a node you encounter is a folder type, do

		cout<<....name.....<<delim;

	If a node you encounter is a file type, do

		cout<<....name.....<<"("<<..size..<<")"<<delim;

	Note: please do NOT include <<endl; (aka newline)
	Example output (assume that the delimiter is a single space):
    
		folder1 file1(0) folder2 file2(0)

    There should be no loop in this function
	See printBtT function for the call to this function.
    This function is private
*/
void MList::traverseToTop(Node* n, string delim){
	if(n != NULL)
	{
		if(n -> nodeData -> isFolder == true)
		{
			cout << n -> nodeData -> name << delim;
		}
		else
		{
			cout<< n -> nodeData -> name <<"("<< n -> nodeData -> size <<")"<<delim;	
		}
		traverseToTop(n -> prev, delim);
	}


    
    
    
    
    

}

/*
	Note: RECURSION --- This function should be implemented using recursion.
	Traverse and print our list from node n to the bottom.
	we will seperate each node printed by the passed-in delimiter.
	If a node you encounter is a folder type, do

		cout<<....name.....<<delim;

	If a node you encounter is a file type, do

		cout<<....name.....<<"("<<..size..<<")"<<delim;

	Note: please do NOT include <<endl; (aka newline)
	Example output (assume that the delimiter is a single space):
    
		folder1 file1(0) folder2 file2(0)

    There should be no loop in this function
	See printTtB function for the call to this function.
    This function is private
*/
void MList::traverseToBottom(Node* n,string delim){
	if(n != NULL)
		{
			if(n -> nodeData -> isFolder == true)
			{
				cout << n -> nodeData -> name << delim;
			}
			else
			{
				cout << n -> nodeData -> name << "(" << n -> nodeData -> size << ")" << delim;
			}
			traverseToBottom(n -> next, delim);
		}

    
    
    
    
}

//------------------------------------------------------------------------------
//FUNCTIONS BELOW ARE COMPLETE, PLEASE DON'T CHANGE ANYTHING HERE
//------------------------------------------------------------------------------

//getting the pointer to the top node.
Node* MList::top(){
	return ntop;
}

//getting the pointer to the bottom node.
Node* MList::bottom(){
	return nbottom;
}

//call traverseToBottom to print all item in the list from bottom node to top node
//the list of items is separated by a given delimiter
void MList::printBtT(string delim){
	//create a temp pointer to hold bottom
	Node* tmp = nbottom;
	traverseToTop(tmp,delim);
}

//call traverseToBottom to print all item in the list from top node to bottom node
//the list of items is separated by a given delimiter
void MList::printTtB(string delim){
	Node* tmp = ntop;
	traverseToBottom(tmp,delim);
}

//call sortSelection function, mode = true = sort by name
//public member
void MList::sortByNameSelection(){
    bool mode = true;
    Node *tmp = ntop;
    sortSelection(tmp,mode);
}

//call sortSelection function, mode = false = sort by size
//public member
void MList::sortBySizeSelection(){
    bool mode = false;
    Node *tmp = ntop;
    sortSelection(tmp,mode);
}

//call sortInsertion function
//public member
void MList::sortByNameInsertion(){
    Node *tmp = ntop;
    sortInsertion(tmp);
}
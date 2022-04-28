#include <iostream>
using namespace std;

#ifndef QueueNode
#define QueueNode

// structure node
template <class T>
struct node
{
	T info;
	node* next;

	// constructor which creates a node with info inf, 
	// which is linked to (i.e. points to) the node 
	// with the pointer nex
	node(T inf, node* nex)
	{
		info = inf;
		next = nex;
	}

	// constructor which creates a node with info inf,
	// which points to NULL
	node(T inf)
	{
		info = inf;
		next = NULL;
	}

	// constructor which creates an empty node, i.e.
	// with uninitialized inf field, which points to NULL
	node()
	{
		next = NULL;
	}
};

// function for printing the list
// argument is the starting node of the list
// Note: as an argument we must enter a *pointer* to the start of the list

template<class T>
void printTheList(T start)
{
	for (T current = start; current != NULL; current = current->next)
	{
		cout << current->info << " -> ";
	}
	cout << "NULL" << endl;
}

#endif

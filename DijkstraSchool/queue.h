#include <iostream>
#include "QueueNode.h"
using namespace std;

#ifndef QUEUE_H
#define QUEUE_H

template <class T>
class QUEUE
{
private:
	typedef node<T> nodeT;
	nodeT* front, * back;

public:
	QUEUE()
	{
		front = NULL;
		back = NULL;
	}

	QUEUE(T inf)
	{
		front = new nodeT(inf);
		back = front;
	}

	T peek()
	{
		return front->info;
	}

	bool isEmpty()
	{
		return (front == NULL);
	}

	int size()
	{
		int g = 0;
		nodeT* current;

		for (current = front; current != NULL; current = current->next)
		{
			g++;
		}

		return g;
	}

	void enqueue(T element)
	{
		nodeT* newnode = new nodeT(element);

		if (isEmpty())	// if the queue is empty
		{
			back = newnode;
			front = newnode;
		}
		else				// if the queue is not empty
		{
			back->next = newnode;
			back = newnode;
		}
	}

	T dequeue()
	{
		if (!isEmpty())
		{
			T v = front->info;
			nodeT* nex = front->next;
			if (back == front)
				back = NULL;
			delete front;
			front = nex;
			return v;
		}
		else
		{
			cout << "The queue is empty!" << endl;
			return (T)NULL;
		}
	}

	void print()
	{
		nodeT* current;

		for (current = front; current != NULL; current = current->next)
		{
			cout << current->info << " -> ";
		}
		cout << "NULL" << endl;
	}
};

#endif
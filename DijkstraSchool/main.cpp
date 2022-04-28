#include <iostream>
using namespace std;
#include "GRAPH.h"
#include "queue.h"

template<class T>
GRAPH<T> Dijkstra(GRAPH<T> g, T veStart)
{
	int numberVertices = g.numberVertices();
	T* vertex = new T[numberVertices];

	g.allVertices(vertex, numberVertices);

	int i, j;
	bool directed;
	int max;
	int queuesize;
	int queueoffsize;
	bool traversed;

	GRAPH<T> copy = g.copy();
	
	GRAPH<T> unit(vertex, numberVertices);

	
	T veFrom, veTo, veFromCurrent, veToCurrent;

	QUEUE<T> queue;
	
	QUEUE<T> queueOff;
	for (i = 0; i < numberVertices; i++)
		queueOff.enqueue(vertex[i]);

	directed = copy.isDirected();

	copy.maxEdge(veFrom, veTo);
	max = copy.weightEdge(veFrom, veTo);

	queuesize = queue.size();

	veFrom = veStart;

	queue.enqueue(veFrom);
	
	while (queueOff.peek() != veFrom)
		queueOff.enqueue(queueOff.dequeue());
	queueOff.dequeue();

	traversed = false;

	while (!traversed)
	{
		if ((queuesize = queue.size()) == copy.numberVertices())
			break;

		int min = max;
		int weightCurrent;

		for (i = 0; i < queuesize; i++)
		{
			veFromCurrent = queue.dequeue();
			copy.minEdgeFrom(veFromCurrent, veToCurrent);

			if (veToCurrent == (T)NULL)
			{
				queue.enqueue(veFromCurrent);
				traversed = true;
				break;
			}

			weightCurrent = copy.weightEdge(veFromCurrent, veToCurrent);
			if ((weightCurrent <= min) && (weightCurrent > 0))
			{
				if (!unit.edgeFromTo(veStart, veToCurrent) && (veToCurrent != veStart))
				{
					min = weightCurrent;
					veFrom = veFromCurrent;
					veTo = veToCurrent;
				}
				else
				{
					traversed = true;
					queue.enqueue(veFromCurrent);
					break;
				}
			}

			queue.enqueue(veFromCurrent);
		}

		if (!traversed)
		{
			unit.setEdge(veFrom, veTo, 1, directed);
			copy.deleteEdge(veFrom, veTo);
			queue.enqueue(veTo);

			while (queueOff.peek() != veTo)
				queueOff.enqueue(queueOff.dequeue());
			queueOff.dequeue();
		}
		else
		{
			if (queue.size() == copy.numberVertices())
				continue;

			else
				if (veToCurrent == (T)NULL)
				{
					copy.deleteVertex(veFromCurrent);
					while (queue.peek() != veFromCurrent)
						queue.enqueue(queue.dequeue());
					queue.dequeue();
				}
				else
					copy.deleteEdge(veFromCurrent, veToCurrent, directed);

			queueoffsize = queueOff.size();
			queuesize = queue.size();
			for (i = 0; i < queuesize; i++)
			{
				for (j = 0; j < queueoffsize; j++)
				{
					if (copy.edgeFromTo(queue.peek(), queueOff.peek()))	
					{
						traversed = false;
						break;
					}

					queueOff.enqueue(queueOff.dequeue());
				}

				if (!traversed)
					break;

				queue.enqueue(queue.dequeue());
			}
		}
	}

	copy = g.copy();

	for (i = 0; i < numberVertices; i++)
		for (j = 0; j < numberVertices; j++)
		{
			if (unit.existEdge(vertex[i], vertex[j]))
				copy.setEdge(vertex[i], vertex[j], g.weightEdge(vertex[i], vertex[j]), directed);
			else
				if (copy.existEdge(vertex[i], vertex[j]))
					copy.deleteEdge(vertex[i], vertex[j], directed);
		}

	return copy;
}

int main(int argc, char* argv[])
{
	char vertex[] = { 'S', 'R', 'G', 'B', 'O', 'T', 'V' };

	int numVertices = sizeof(vertex) / sizeof(char);

	GRAPH<char> g(vertex, numVertices);

	g.setEdge('S', 'R', 10, true);
	g.setEdge('B', 'S', 80, true);
	g.setEdge('S', 'T', 120, true);
	g.setEdge('G', 'R', 40, true);
	g.setEdge('R', 'O', 60, true);
	g.setEdge('R', 'V', 120, true);
	g.setEdge('R', 'T', 90, true);
	g.setEdge('O', 'G', 100, true);
	g.setEdge('G', 'B', 30, true);
	g.setEdge('O', 'B', 80, true);
	g.setEdge('T', 'O', 20, true);
	g.setEdge('V', 'T', 30, true);

	cout << "\nThe graph g:" << endl;
	g.print();
	cout << endl;

	cout << "\nThe graph g:" << endl;
	g.print();
	cout << endl;
	QUEUE<char> dfs;

	char findMother;

	for (int i = 0; i < 7; ++i)
	{
		g.DFS(g,vertex[i], dfs);
		if (dfs.size() == 9)
		{
			findMother = vertex[i];
		}
	}

		GRAPH<char> tree = Dijkstra(g, findMother);

		cout << "\nThe minimal spanning tree according Dijkstra's algorithm, starting at " << findMother << ": " << endl;
		tree.print();
	
}

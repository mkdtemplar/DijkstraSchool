#include <iostream>
#include "queue.h"
#include <ctime>
#include <cstdlib>
#ifndef GRAPH_H
#define GRAPH_H


const int MAXSIZE = 12;
using namespace std;


template <class T>
class GRAPH
{
private:
	unsigned int v[MAXSIZE][MAXSIZE];
	T VERTEX[MAXSIZE];
	unsigned int size;

public:
	// the index of a VERTEX with value ve
	int indexOfVertex(T ve)
	{
		int val = -1;
		if (existVertex(ve))
		{
			for (int i = 0; i < size; i++)
				if (VERTEX[i] == ve)
				{
					val = i;
					break;
				}
		}
		else
			cout << "ERROR! An attempt to find a value of a vertex that does not exist!" << endl;

		return val;
	}

	// constructor
	GRAPH()
	{
		this->size = 0;
		for (int i = 0; i < MAXSIZE; i++)
		{
			VERTEX[i] = (T)(NULL);
			for (int j = 0; j < MAXSIZE; j++)
				v[i][j] = 0;
		}
	}

	// creates a graph with predefined size
	GRAPH(int size)
	{
		if (size < MAXSIZE)
		{
			this->size = size;
			for (int i = 0; i < MAXSIZE; i++)
			{
				VERTEX[i] = (T)(NULL);
				for (int j = 0; j < MAXSIZE; j++)
					v[i][j] = 0;
			}
		}
		else
		{
			cout << "ERROR! The graph can have maximum " << MAXSIZE << " vertices!" << endl;
		}
	}

	// creates a graph with predefined values of the vertices
	GRAPH(T VERTEX[], int size)
	{
		int i, j;
		if (size < MAXSIZE)
		{
			this->size = size;

			for (i = 0; i < MAXSIZE; i++)
				for (j = 0; j < MAXSIZE; j++)
					v[i][j] = 0;

			for (i = 0; i < size; i++)
				this->VERTEX[i] = VERTEX[i];
		}
		else
		{
			cout << "ERROR! The graph can have maximum " << MAXSIZE << " vertices!" << endl;
		}
	}

	// printing the graph
	void print()
	{
		for (int i = 0; i < size; i++)
		{
			cout << VERTEX[i] << ": ";
			for (int j = 0; j < size; j++)
				if (v[i][j] != 0)
					cout << VERTEX[j] << "(" << v[i][j] << ") ";
			cout << endl;
		}
	}

	// Is there a vertex with value ve?
	bool existVertex(T ve)
	{
		bool exist = false;

		for (int i = 0; i < size; i++)
		{
			if (VERTEX[i] == ve)
			{
				exist = true;
				break;
			}

			if (exist)
				break;
		}

		return exist;
	}

	// changing the value of an existing vertex
	void setVertex(T ve, T newValue)
	{
		if (existVertex(ve))
		{
			VERTEX[indexOfVertex(ve)] = newValue;
		}
		else
		{
			cout << "ERROR! An attempt to change the value of a vertex that does not exist!" << endl;
		}
	}

	// adds a new vertex
	void addVertex(T ve)
	{
		int i;
		if (size >= MAXSIZE)
		{
			cout << "ERROR! An attempt to add a vertex in a graph which already has tha maximum number of vertices!" << endl;
		}
		else
		{
			for (i = 0; i < MAXSIZE; i++)
				if (VERTEX[i] == (T)(NULL))
					break;

			VERTEX[i] = ve;

			size++;
		}
	}

	// deleting a vertex
	void deleteVertex(T ve)
	{
		int i, j;
		if (existVertex(ve))
		{
			int ind = indexOfVertex(ve);
			for (j = 0; j < MAXSIZE; j++)
			{
				v[ind][j] = 0;
				v[j][ind] = 0;
			}

			VERTEX[ind] = (T)(NULL);

			// Defragmentation ...
			for (i = ind + 1; i < MAXSIZE; i++)
				for (j = 0; j < MAXSIZE; j++)
					v[i - 1][j] = v[i][j];

			for (j = ind + 1; j < MAXSIZE; j++)
			{
				VERTEX[j - 1] = VERTEX[j];

				for (i = 0; i < MAXSIZE; i++)
					v[i][j - 1] = v[i][j];
			}

			size--;		// the size of the graph is now one vertex smaller

			// deleting the last row and column
			for (i = 0; i < MAXSIZE; i++)
			{
				v[i][size] = 0;
				v[size][i] = 0;
			}
			VERTEX[size] = (T)(NULL);
		}
		else
		{
			cout << "ERROR! An attempt to delete a vertex that does not exist!" << endl;
		}
	}

	// number of edges ...
	int numberEdges()
	{
		int n = 0, i, j;

		for (i = 0; i < size; i++)
			for (j = 0; j < size; j++)
			{
				if (i == j)
					continue;
				if (v[i][j] != 0)
					n++;
			}

		if (!this->isDirected())
			n /= 2;

		for (i = 0; i < size; i++)
			if (v[i][i] != 0)
				n++;

		return n;
	}

	// number of vertices ...
	int numberVertices()
	{
		return size;
	}

	// Does all the edges have a value of 1 (matrix of ones)?
	bool isUnit()
	{
		bool is = true;
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
				if ((v[i][j] != 1) && (v[i][j] != 0))
				{
					is = false;
					break;
				}
			if (!is)
				break;
		}

		return is;
	}

	// Is the graph directed?
	bool isDirected()
	{
		bool d = false;

		for (int i = 0; i < size; i++)
		{
			for (int j = i; j < size; j++)
				if (v[i][j] != v[j][i])
				{
					d = true;
					break;
				}
			if (d)
				break;
		}

		return d;
	}

	// setting an edge ...
	void setEdge(T ve1, T ve2, int value, bool directed = false)
	{
		if (existVertex(ve1) && existVertex(ve2))
		{
			v[indexOfVertex(ve1)][indexOfVertex(ve2)] = value;
			if (!directed)
				v[indexOfVertex(ve2)][indexOfVertex(ve1)] = value;
		}
		else
			cout << "ERROR! An attempt to add an edge between non-existant vertices!" << endl;
	}

	// deleting an edge ...
	void deleteEdge(T ve1, T ve2, bool directed = false)
	{
		if (existVertex(ve1) && existVertex(ve2))
		{
			v[indexOfVertex(ve1)][indexOfVertex(ve2)] = 0;
			if (!directed)
				v[indexOfVertex(ve2)][indexOfVertex(ve1)] = 0;
		}
		else
			cout << "ERROR! An attempt to delete an edge between non-existant vertices!" << endl;
	}

	// checks if an edge exists between two vertices?
	bool existEdge(T ve1, T ve2)
	{
		if (existVertex(ve1) && existVertex(ve2))
			if (v[indexOfVertex(ve1)][indexOfVertex(ve2)] == 0)
				return false;
			else
				return true;
		else
		{
			cout << "ERROR! An attempt to check an edge between non-existant vertices!" << endl;
			return false;
		}
	}

	// edge weight ...
	int weightEdge(T ve1, T ve2)
	{
		if (existEdge(ve1, ve2))
			return v[indexOfVertex(ve1)][indexOfVertex(ve2)];
		else
			return -1;
	}


	// creates a graph with random values between given vertices
	void makeRandom(T* VERTEX, int size, unsigned int maxWeight = 1, bool directed = false)
	{
		srand(time(NULL));

		this->size = size;

		for (int i = 0; i < MAXSIZE; i++)
		{
			if (i >= size)
				for (int j = 0; j < MAXSIZE; j++)
					v[i][j] = 0;
			else
				this->VERTEX[i] = VERTEX[i];
		}

		if (directed)
			for (int i = 0; i < size; i++)
				for (int j = 0; j < size; j++)
					v[i][j] = rand() % (maxWeight + 1);
		else
			for (int i = 0; i < size; i++)
				for (int j = i; j < size; j++)
				{
					v[i][j] = rand() % (maxWeight + 1);
					v[j][i] = v[i][j];
				}

		for (int i = 0; i < size; i++)
			v[i][i] = 0;
	}



	// returns an array (and its size) of adjacent vertices to a given vertex
	void adjacentTo(T ve, T*& adjacent, int& numAdjacent)
	{
		numAdjacent = 0;

		if (existVertex(ve))
		{
			for (int i = 0; i < size; i++)
				if (v[indexOfVertex(ve)][i] != 0)
					numAdjacent++;

			adjacent = new T[numAdjacent];
			int a = 0;

			for (int i = 0; i < size; i++)
				if (v[indexOfVertex(ve)][i] != 0)
				{
					adjacent[a] = VERTEX[i];
					a++;
				}
		}
		else
			cout << "ERROR! An attempt to find neighboring vertices to a non-existant vertex!" << endl;
	}



	// returns all the vertices in the graph
	void allVertices(T*& VERTEX, int& numVertices)
	{
		numVertices = size;

		VERTEX = new T[size];


		for (int i = 0; i < size; i++)
			VERTEX[i] = this->VERTEX[i];
	}

	// returns a copy of the given graph
	GRAPH<T> copy()
	{
		int i, j;

		GRAPH<T> f;

		f.size = this->size;

		for (i = 0; i < f.size; i++)
		{
			f.VERTEX[i] = this->VERTEX[i];

			for (j = 0; j < f.size; j++)
				f.v[i][j] = this->v[i][j];
		}

		return f;
	}

	// returns a completely connected transitive digraph according the Warshall algorithm
	GRAPH<T> Warshall()
	{
		GRAPH<T> f = this->copy();

		int numVertices = f.numberVertices();

		for (int i = 0; i < numVertices; i++)
			for (int v = 0; v < numVertices; v++)
				for (int w = 0; w < numVertices; w++)
					if ((f.v[v][i] != 0) && (f.v[i][w] != 0))
						f.v[v][w] = 1;

		return f;
	}

	// checks if an edge exists between two vertices, given with their values
	bool edgeFromTo(T veFrom, T veTo)
	{
		// coping ...
		GRAPH<T> f = this->Warshall();

		// if there is an edge between two adjacent vertices after the
		// application of the Warshall algorithm on the copy, then there
		// is an edge between them in the original graph; otherwise there isn't
		return f.existEdge(veFrom, veTo);
	}


	// returns the two vertices, among which is the edge with the maximum weight in the graph
	void maxEdge(T& veFrom, T& veTo)
	{
		int max = 0, i, j;

		for (i = 0; i < this->size; i++)
			for (j = 0; j < this->size; j++)
				if (this->weightEdge(VERTEX[i], VERTEX[j]) > max)
				{
					max = this->weightEdge(VERTEX[i], VERTEX[j]);
					veFrom = VERTEX[i];
					veTo = VERTEX[j];
				}

		if (max <= 0)
		{
			veFrom = (T)NULL;
			veTo = (T)NULL;
		}
	}

	// returns the two vertices, among which is the edge with the minimum weight in the graph
	void minEdge(T& veFrom, T& veTo)
	{
		int i, j;

		// initially, the minimum weight is the maximum one in the graph
		maxEdge(veFrom, veTo);
		if ((veFrom == (T)NULL) || (veTo == (T)NULL))
			return;
		int min = weightEdge(veFrom, veTo);
		int weight;

		for (i = 0; i < size; i++)
			for (j = 0; j < size; j++)
			{
				weight = weightEdge(VERTEX[i], VERTEX[j]);
				if ((weight < min) && (weight > 0))
				{
					min = weight;
					veFrom = VERTEX[i];
					veTo = VERTEX[j];
				}
			}
	}

	// returns the vertex to which there is an edge with minimum weight, starting from a specified vertex
	void minEdgeFrom(T veFrom, T& veTo)
	{
		int j;

		T temp;
		int max;

		bool found = false;
		for (j = 0; j < this->size; j++)
			if (v[indexOfVertex(veFrom)][indexOfVertex(this->VERTEX[j])] != 0)
			{
				found = true;
				break;
			}

		if (found)
		{
			this->maxEdge(temp, veTo);
			max = this->weightEdge(temp, veTo);
		}
		else
		{
			veTo = (T)NULL;
			return;
		}

		int weight = -1;

		int min = max;

		for (j = 0; j < this->size; j++)
		{
			if (existEdge(veFrom, this->VERTEX[j]))
			{
				weight = this->weightEdge(veFrom, this->VERTEX[j]);
				if (weight <= min)
				{
					min = weight;
					veTo = VERTEX[j];
				}
			}
		}

		if (weight == -1)
			veTo = (T)NULL;
	}

	void DFS(GRAPH<T> g, T ve, QUEUE<T>& result)
	{
		T current, * adjacent;

		// current vertex being processed, array of adjacent vertices to the current vertex

		int numAdjacent;
		// the number of adjacent vertices to the vertex being processed

		int i, j;
		// counters

		if (g.existVertex(ve))

			// if the given vertex exists in the graph for which DFS traversal is demanded
		{
			result.enqueue(ve); //enter it in the resulting queue
			current = ve;

			// make it a current vertex

			g.adjacentTo(current, adjacent, numAdjacent);
			// all vertices adjacent to it are obtained and their number

			for (i = 0; i < numAdjacent; i++)
				// for each of the adjacent vertices
			{
				// test all vertices in the traversal queue
				// if the adjacent vertex isn't there, put it there
				// and invoke a recursive call

				int numResult = result.size();
				// obtain the size of the array of adjacent vertices

				bool traversed = false;
				// state that initially the current vertex has not been traversed

				for (j = 0; j < numResult; j++)
					// for every adjacent vertex
				{
					if (result.peek() == adjacent[i])
						// if the adjacent vertex is in the resulting queue
						traversed = true; //it means that it has been traversed

					result.enqueue(result.dequeue()); // cycle the vertex from the start to the end of the queue
				}

				if (!traversed)
					// if the current vertex has not been traversed
					DFS(g, adjacent[i], result);
				// invoke a recursive call starting from that vertex,
				// with the result queue passed again by reference
			}
		}
		else
			// if the vertex, for which DFS traversal is demanded, doesn't exist
		{
			cout << "ERROR! Vertex " << ve << " is not a part of the given graph!" << endl;
		}
	}

};


#endif

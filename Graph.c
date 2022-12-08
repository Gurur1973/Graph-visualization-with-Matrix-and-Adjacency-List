#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"
typedef struct LINKED_LIST_NODE_s *LINKED_LIST_NODE;
typedef struct LINKED_LIST_NODE_s
{
	LINKED_LIST_NODE next;
	void *data;
} LINKED_LIST_NODE_t[1];

typedef struct LINKED_LIST_s *LINKED_LIST;
typedef struct LINKED_LIST_s
{
	LINKED_LIST_NODE head; 
} LINKED_LIST_t[1], *LINKED_LIST;


typedef struct // Edge struct
{
	int source;
	int destination;
} EDGE;

typedef struct // Graph struct with edges array
{
	int num_vertices;
	int num_edges;
	EDGE *edges;

} GRAPH;

GRAPH *createGraph(int vertices, int edges);
void fillGraph(GRAPH *graph);

GRAPH *createGraph(int vertices, int edges) // Allocate memory with given vertices and edges sizes
{
	GRAPH *graph = calloc(1, sizeof(*graph));
	if (graph == NULL)
	{
		printf("Error:");
		exit(EXIT_FAILURE);
	}

	graph->num_vertices = vertices;
	graph->num_edges = edges;
	graph->edges = calloc(edges, sizeof(EDGE));

	if (graph->edges == NULL)
	{
		printf("Error:");
		exit(EXIT_FAILURE);
	}
	return graph;
}


void fillGraph(GRAPH *graph) // Define edges manually
{
	graph->edges[0].source = 1;
	graph->edges[0].destination = 2;

	graph->edges[1].source = 1;
	graph->edges[1].destination = 3;

	graph->edges[2].source = 1;
	graph->edges[2].destination = 4;

	graph->edges[3].source = 2;
	graph->edges[3].destination = 4;

	graph->edges[4].source = 2;
	graph->edges[4].destination = 5;

	graph->edges[5].source = 4;
	graph->edges[5].destination = 3;

	graph->edges[6].source = 4;
	graph->edges[6].destination = 5;
}



int **createMatrix(GRAPH *graph) // Create a matrix with given graph
{

	int **matrix = (int **)malloc(sizeof(int *) * graph->num_vertices);
	for (int i = 0; i < graph->num_vertices; i++)
	{
		matrix[i] = (int *)malloc(sizeof(int) * graph->num_vertices);
	}

	for (int i = 0; i < graph->num_vertices; i++)
	{
		for (int j = 0; j < graph->num_vertices; j++)
		{
			matrix[i][j] = 0;
		}
	}

	for (int i = 0; i < graph->num_edges; i++)
		matrix[graph->edges[i].source - 1][graph->edges[i].destination - 1] = 1;

	return matrix;
}


void printMatrix(int **matrix, int size) // Print the given matrix
{
	
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			printf("%d ", matrix[i][j]);
		}
		printf("\n");
	}
}


LINKED_LIST newList() // Creating new list with first node null
{
	LINKED_LIST list = (LINKED_LIST)malloc(sizeof(LINKED_LIST_t));
	list->head = NULL;
	return list;
}

LINKED_LIST_NODE newNode(void *data)
{
	LINKED_LIST_NODE node = (LINKED_LIST_NODE)malloc(sizeof(LINKED_LIST_NODE_t));
	node->next = NULL;
	node->data = data;
	return node;
}


void addLast(LINKED_LIST list, LINKED_LIST_NODE node) // Insert the given node to the end of the given list
{
	LINKED_LIST_NODE root = list->head;
	if (root == NULL)
	{
		list->head = node;
		list->head->next = NULL;
	}
	else
	{
		while (root->next != NULL)
		{
			root = root->next;
		}
		root->next = node;
		node->next = NULL;
	}
}




LINKED_LIST **createAdjList(int **matrix, int size)
{

	LINKED_LIST **adjList = (LINKED_LIST **)malloc(sizeof(LINKED_LIST *) * size);
	for (int i = 0; i < size; i++)
	{
		adjList[i] = newList();
	}

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (matrix[i][j] == 1)
			{
				addLast(adjList[i], newNode(j));
			}
		}
	}

	return adjList;
}

void printAdjList(LINKED_LIST **adjList, int size)
{

	for (int i = 0; i < size; i++)
	{
		LINKED_LIST tempList = adjList[i];
		LINKED_LIST_NODE root = tempList->head;
		printf("%d", i + 1);
		while (root != NULL)
		{
			printf("-> %d", root->data + 1);
			root = root->next;
		}
		printf("\n");
	}
}
 


int main()
{

	GRAPH *graph = createGraph(5, 7);  // Creating graph
	fillGraph(graph); // Fill the graph with given edges


	int **matrix = createMatrix(graph); // Create the matrix version of graph
	printf("The matrix version of graph :\n");
	printMatrix(matrix, graph->num_vertices);


	LINKED_LIST **adjList = createAdjList(matrix,graph->num_vertices); // Create adjacency list of graph
	printf("\nSorted list with Depth First Search: \n");
	printAdjList(adjList,graph->num_vertices); // The output's values start from 1 not 0 (first node is 1)

    return 0;
}



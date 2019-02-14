#ifndef GRAPH_H_
#define GRAPH_H_

#include <stdbool.h>
#include "vertex.h"

// Graph data structure
typedef struct graph {
	int number_of_vertices;
	vertex *vertices;
} graph;

/*
 * Reads in the file from the given filename
 * and build a graph from the input.
 */
graph *read_graph(char *filename);

// Sets up the graph by initializing vertices and edges
graph *initialize_graph(int number_of_vertices, int **matrix);

// Tells if the graph has any edges
bool graph_has_edges(graph *g);

// Returns a list of the vertices which have no incoming edges.
linked_list *get_source_vertices(graph *g);

// Removes the edge from a to b.
void remove_edge(vertex *a, vertex *b);

/*
 * Debug method, that can print information on a supplied graph.
 */
void print_graph(graph *g);

// Teardown the given matrix
void kill_matrix(int** matrix, int size);

// Teardown the graph
void kill_graph(graph *g);

#endif

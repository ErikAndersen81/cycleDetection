#ifndef VERTEX_H_
#define VERTEX_H_

#include "linked_list.h"

// Datastructure for a vertex in a graph
typedef struct vertex {
	int id;
	linked_list *direct_successors;
	linked_list *direct_predecessors;
} vertex;

// Initializes the specified number of vertices (without any edges)
vertex *initialize_vertices(int number_of_vertices);

// Teardown the vertex
void kill_vertex(vertex *v);

#endif /* VERTEX_H_ */

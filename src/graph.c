#include <stdlib.h>
#include "graph.h"
#include <stdio.h>

// Reads int from first line of file
int get_number_of_vertices(FILE *file);

// Reads an adjacency matrix into a two-dimensional array
int **get_adjacency_matrix(int number_of_vertices, FILE *file);

graph *read_graph(char *filename) {
  FILE *file = fopen(filename, "r");
  int number_of_vertices = get_number_of_vertices(file);
  int **matrix = get_adjacency_matrix(number_of_vertices, file);
  fclose(file);
  graph *G = initialize_graph(number_of_vertices, matrix);
  kill_matrix(matrix, number_of_vertices);
  return G;
}


int get_number_of_vertices(FILE *file) {
  int number_of_vertices = 0;
  int n = fgetc(file);
  while (n != 10) {
    number_of_vertices = 10*number_of_vertices + (n - 48);
    n = fgetc(file);
  }
  return number_of_vertices;
}


int **get_adjacency_matrix(int number_of_vertices, FILE *file) {
  int **matrix = (int**) malloc(sizeof(int*) * number_of_vertices);
  for (int n=0; n<number_of_vertices; n++) {
    matrix[n] =  malloc(sizeof(int) * number_of_vertices);
    for (int m=0; m<number_of_vertices; m++) {
      matrix[n][m] = fgetc(file) - 48;
    }
    fgetc(file); // dispose of newline char
  }
  return matrix;
}


graph *initialize_graph(int number_of_vertices, int **matrix){
  graph *g = (graph*) malloc(sizeof(graph));
  g->number_of_vertices = number_of_vertices;
  g->vertices = initialize_vertices(number_of_vertices);
  // Setup direct predecessors and direct successors of each vertex according to adjacency matrix
  for (int i=0; i<number_of_vertices; i++) {
    for (int n=0; n<number_of_vertices; n++) {
      if (matrix[i][n] == 1) {
	add_element(g->vertices[i].direct_successors, &g->vertices[n]);
      }
      if (matrix[n][i] == 1) {
	add_element(g->vertices[i].direct_predecessors, &g->vertices[n]);
      }
    }
  }
  return g;
}


vertex *initialize_vertices(int number_of_vertices) {
  vertex *vertices = (vertex*) malloc(sizeof(vertex) * number_of_vertices);
  for (int i=0; i<number_of_vertices; i++) {
    vertices[i].id = i;
    vertices[i].direct_successors = init_linked_list();
    vertices[i].direct_predecessors = init_linked_list();
  }
  return vertices;
}


void print_graph(graph *g) {
  printf("The graph has %d vertices.\n\n", g->number_of_vertices);
  for (int i=0; i<g->number_of_vertices; i++) {
    vertex *v = &g->vertices[i];
    printf("id: %d \n",v->id);
    printf("\tdirect successors: ");
    linked_list *out_vertices = (linked_list*) v->direct_successors;
    while (out_vertices != NULL && out_vertices->data != NULL) {
      vertex *p = (vertex*) out_vertices->data;
      printf("%d ", p->id);
      out_vertices = out_vertices->next;
    }
    printf("\n\tdirect predecessors: ");
    linked_list *in_vertices = (linked_list*) v->direct_predecessors;
    while (in_vertices != NULL && in_vertices->data != NULL) {
      vertex *p = (vertex*) in_vertices->data;
      printf("%d ", p->id);
      in_vertices = in_vertices->next;
    }
    printf("\n");
  }
}


void kill_matrix(int** matrix, int size) {
  for (int n=0; n<size; n++) {
    free(matrix[n]);
  }
  free(matrix);
}


void kill_vertex(vertex *v) {
  kill_linked_list(v->direct_predecessors);
  kill_linked_list(v->direct_successors);
}


void kill_graph(graph *g) {
  for (int i=0; i<g->number_of_vertices; i++) {
    kill_vertex((vertex*) &g->vertices[i]);
  }
  free(g->vertices);
  free(g);
}

#include <stdlib.h>
#include <stdio.h>
#include "graph.h"

void print_result(graph *g, linked_list *L);

/* 
 * Uses Kahn's Algorithm to generate a topological sort
 * which is printed to stdtout.
 * That is, it only works on acyclic graphs.
 */
void cycle_detection(graph *g) {
  linked_list *L = init_linked_list();
  linked_list *S = get_source_vertices(g);
  while(linked_list_size(S) > 0) {
    vertex *n = (vertex*) S->data;
    remove_element(S, n);
    add_element(L, n);
    vertex *m;
    while (linked_list_size(n->direct_successors) > 0){
      m = (vertex*) n->direct_successors->data;
      remove_edge(n,m);
      if (linked_list_size(m->direct_predecessors) == 0) {
	add_element(S, m);
      }
    }
  }
  print_result(g, L);
  kill_graph(g);
  kill_linked_list(L);
  kill_linked_list(S);
}


linked_list *get_source_vertices(graph *g) {
  linked_list *S = init_linked_list();
  for (int i=0; i<g->number_of_vertices; i++) {
    if (linked_list_size(g->vertices[i].direct_predecessors) == 0) {
      add_element(S, &g->vertices[i]);
    }
  }
  return S;
}


void remove_edge(vertex *a, vertex *b) {
  int a1 = remove_element(a->direct_successors, b);
  int b1 = remove_element(b->direct_predecessors, a);
}


void print_result(graph *g, linked_list *L) {
  if (graph_has_edges(g)) {
    printf("CYCLE DETECTED!\n");
    return;
  }
  while (L != NULL) {
    vertex *v = (vertex*) L->data;
    printf("%d",v->id);
    if (L->next != NULL) printf(", ");
    else printf("\n");			   
    L = L->next;
  }
}


bool graph_has_edges(graph* g) {
  for (int i=0; i<g->number_of_vertices; i++) {
    if (linked_list_size(g->vertices[i].direct_successors) > 0) return true;
    if (linked_list_size(g->vertices[i].direct_predecessors) > 0) return true;
  }
  return false;
}


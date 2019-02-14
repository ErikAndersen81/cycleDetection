/*
 * linked_list.c
 *
 *  Created on: Dec 24, 2013
 *      Author: jacob
 */
#include "linked_list.h"
#include <stdlib.h>
#include <stdio.h>

linked_list* linked_list_last(linked_list* node);


linked_list *init_linked_list() {
  linked_list *node = (linked_list*) malloc(sizeof(linked_list));
  node->data = NULL;
  node->next = NULL;
  node->previous = NULL;
  return node;
}


void add_element(linked_list *list, void *element) {
  // The list is empty
  if (list->data == NULL) {
    list->data = element;
  }
  // The list is not empty
  else {
    linked_list *new_node = init_linked_list();
    linked_list *last_node = linked_list_last(list);
    new_node->data = element;
    new_node->next = NULL;
    new_node->previous = last_node;
    last_node->next = new_node;
  }
  return;
}


int linked_list_size(linked_list *list) {
  int size = (list->data == NULL)?  0 : 1;
  while (list->next != NULL) {
    size++;
    list = list->next;
  }
  return size;
}


int remove_element(linked_list *node, void *element) {
  while (node != NULL) {
    if (element == node->data)
      {
	// only element in the list
	if (node->previous == NULL && node->next == NULL) {
	  node->data = NULL;
	}
	// last element in the list
	else if (node->next == NULL) {
	  node->previous->next = NULL;
	  free(node);
	}
	// first element in the list
	// copies "next" node to this node and removes "next" node
	else if (node->previous == NULL) {
	  linked_list *new_next = node->next->next;
	  node->data = node->next->data;
	  free(node->next);
	  node->next = new_next;
	  if (node->next != NULL) {
	    node->next->previous = node;
	  }
	}
	// Any other placement in the list
	else {
	  node->previous->next = node->next;
	  node->next->previous = node->previous;
	  free(node);
	}
	return 0;
      }
    node = node->next;
  }
  return -1;
}


linked_list* linked_list_last(linked_list* node) {
  while (node->next != NULL) {
    node = node->next;
  }
  return node;
}


void kill_linked_list(linked_list *list) {
  int count = linked_list_size(list);
  for (int i=0; i<count; i++) {
    remove_element(list, list->data);
  }
  free(list);
}

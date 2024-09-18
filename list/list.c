// list/list.c
// 
// Implementation for linked list.
//
// Priyanka Ghimire

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

// Allocates memory for a new list and initializes its head to NULL
list_t *list_alloc() { 
  list_t* mylist = (list_t *) malloc(sizeof(list_t)); 
  mylist->head = NULL;
  return mylist;
}

// Frees all nodes in the list and the list itself
void list_free(list_t *l) {
  if (l == NULL) {
    return;
  }

  node_t *current = l->head;
  node_t *next_node;

  while (current != NULL) {
    next_node = current->next;
    free(current);
    current = next_node;
  }

  free(l);  // Don't forget to free the list structure itself
}

// Prints all elements of the list
void list_print(list_t *l) {
  if (l == NULL) {
    printf("List is NULL\n");
    return;
  }

  node_t *current = l->head;

  if (current == NULL) {
    printf("List is empty\n");
    return;
  }

  while (current != NULL) {
    printf("%d -> ", current->value);
    current = current->next;
  }

  printf("NULL\n");
}

// Converts the list to a string and returns it
char * listToString(list_t *l) {
  char* buf = (char *) malloc(sizeof(char) * 10024); // Allocate large buffer
  char tbuf[20];

  node_t* curr = l->head;
  while (curr != NULL) {
    sprintf(tbuf, "%d->", curr->value);
    strcat(buf, tbuf);
    curr = curr->next;
  }
  strcat(buf, "NULL");
  return buf;
}

// Returns the length of the list
int list_length(list_t *l) { 
  node_t *current = l->head;
  int count = 0;

  while (current != NULL) {
    count++;
    current = current->next;
  }
  return count; 
}

// Adds a node with the specified value to the back of the list
void list_add_to_back(list_t *l, elem value) {
  node_t *cur_node = getNode(value);

  if (l->head == NULL) {
    l->head = cur_node;
  } else {
    node_t *current = l->head;
    while (current->next != NULL) {
      current = current->next;
    }
    current->next = cur_node;
  }
}

// Adds a node with the specified value to the front of the list
void list_add_to_front(list_t *l, elem value) {
  node_t *cur_node = getNode(value);

  cur_node->next = l->head;
  l->head = cur_node;
}

// Allocates and initializes a new node with the given value
node_t * getNode(elem value) {
  node_t *mynode = (node_t *) malloc(sizeof(node_t));
  mynode->value = value;
  mynode->next = NULL;
  return mynode;
}

// Adds a node with the specified value at a given index
void list_add_at_index(list_t *l, elem value, int index) {
  if (index == 0) {
    list_add_to_front(l, value);
  } else {
    node_t *cur_node = getNode(value);
    node_t *current = l->head;
    int current_index = 0;

    while (current != NULL && current_index < index - 1) {
      current = current->next;
      current_index++;
    }

    cur_node->next = current->next;
    current->next = cur_node;
  }
}

// Removes the last node from the list and returns its value
elem list_remove_from_back(list_t *l) { 
  if (l == NULL || l->head == NULL) {
    return -1;
  } 

  if (l->head->next == NULL) {
    elem value = l->head->value;
    free(l->head);
    l->head = NULL;
    return value;
  }

  node_t *current = l->head;
  while (current->next->next != NULL) {
    current = current->next;
  }

  node_t *last_node = current->next;
  elem value = last_node->value;
  free(last_node);
  current->next = NULL;

  return value;
}

// Removes the first node from the list and returns its value
elem list_remove_from_front(list_t *l) { 
  if (l == NULL || l->head == NULL) {
    return -1;
  } 

  node_t *node_to_remove = l->head;
  elem value = node_to_remove->value;
  l->head = node_to_remove->next;
  free(node_to_remove);

  return value;
}

// Removes the node at the specified index and returns its value
elem list_remove_at_index(list_t *l, int index) {
  if (l == NULL || l->head == NULL) {
    return -1;
  } 

  if (index == 0) {
    return list_remove_from_front(l);
  }

  node_t *current = l->head;
  int current_index = 0;

  while (current != NULL && current_index < index - 1) {
    current = current->next;
    current_index++;
  }

  if (current == NULL || current->next == NULL) {
    return -1; 
  }

  node_t *node_to_remove = current->next;
  elem value = node_to_remove->value;
  current->next = node_to_remove->next;
  free(node_to_remove);

  return value;
}

// Checks if a value exists in the list
bool list_is_in(list_t *l, elem value) { 
  if (l == NULL) {
    return false; 
  }

  node_t *current = l->head;

  while (current != NULL) {
    if (current->value == value) {
      return true;
    }
    current = current->next;
  }

  return false;
}

// Gets the value of the node at the specified index
elem list_get_elem_at(list_t *l, int index) { 
  if (l == NULL || index < 0) {
    return -1;
  }

  node_t *current = l->head;
  int current_index = 0;

  while (current != NULL) {
    if (current_index == index) {
      return current->value;
    }
    current = current->next;
    current_index++;
  }

  return -1;
}

// Gets the index of a node with the specified value
int list_get_index_of(list_t *l, elem value) { 
  if (l == NULL) {
    return -1;
  }

  node_t *current = l->head;
  int current_index = 0;

  while (current != NULL) {
    if (current->value == value) {
      return current_index;
    }
    current = current->next;
    current_index++;
  }

  return -1;
}

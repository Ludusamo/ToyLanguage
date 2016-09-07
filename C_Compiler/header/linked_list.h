#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "stdio.h"
#include "stdlib.h"

typedef struct Link Link;

struct Link {
	int val;
	struct Link *next;
	struct Link *prev;
};

typedef struct {
	Link *head;
	Link *tail;
	int length;
} Linked_List;

Linked_List *create_linked_list();
void destroy_linked_list(Linked_List *list);

int add_link(Linked_List *list, int val);
int remove_link(Linked_List *list, int val);

#endif // LINKEDLIST_H

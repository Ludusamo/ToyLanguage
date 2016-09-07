#include "linked_list.h"

Linked_List *create_linked_list() {
	Linked_List *list = malloc(sizeof(Linked_List));
	list->head = 0;
	list->tail = 0;
	list->length = 0;
	return list;
}

void destroy_linked_list(Linked_List *list) {
	Link *head = list->head;	
	Link *buf;
	while (head) {
		buf = head;
		head = head->next;
		free(buf);
		buf = 0;
	}
}

int add_link(Linked_List *list, int val) {
	Link *tail = list->tail;
	Link *new_link = malloc(sizeof(Link));
	new_link->next = 0;
	new_link->prev = tail;
	new_link->val = val;
	if (!tail) {
		list->head = new_link;
		list->tail = new_link;
	} else {
		list->tail->next = new_link;
		list->tail = list->tail->next;
	}
	list->length++;
	return 1;
}

int remove_link(Linked_List *list, int val) {
	Link *head = list->head;
	Link *next = head->next;
	if (head->val == val) {
		list->head = next;
		list->length--;
		return 1;
	}
	while (next) {
		if (next->val == val) {
			head->next = next->next;
			if (next == list->tail) list->tail = (head->next) ? head->next : head;
			free(next);
			next = 0;
			list->length--;
			return 1;
		}
		head = next;
		next = next->next;
	}
	return 0;
}

#include "pda.h"

void if_execute(PDA *pda) {
	Linked_List *instructions = (Linked_List *) pda->data[0];
	Link *branch_location = (Link *) pda->data[1];
	branch_location->val = instructions->length;
}

PDA *create_if_pda(Linked_List *instructions, Link *branch_location) {
	PDA *pda = malloc(sizeof(PDA));
	pda->data = calloc(sizeof(void*), 2);
	pda->data[0] = (void *) instructions;
	pda->data[1] = (void *) branch_location;
	pda->execute = &if_execute;
}

void function_execute(PDA *pda) {
	Linked_List *instructions = (Linked_List *) pda->data[0];
	Link *branch_location = (Link *) pda->data[1];
	add_link(instructions, PUSH_OP);
	add_link(instructions, 0);
	add_link(instructions, RET_OP);
	branch_location->val = instructions->length;
}

PDA *create_func_pda(Linked_List *instructions, Link *branch_location) {
	PDA *pda = malloc(sizeof(PDA));
	pda->data = calloc(sizeof(void*), 2);
	pda->data[0] = (void *) instructions;
	pda->data[1] = (void *) branch_location;
	pda->execute = &function_execute;
}

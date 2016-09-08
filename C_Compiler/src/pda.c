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
	return pda;
}

void while_execute(PDA *pda) {
	Linked_List *instructions = (Linked_List *) pda->data[0];
	Link *branch_location = (Link *) pda->data[1];
	int *beg_branch_index = (int *) pda->data[2];
	add_link(instructions, BR_OP);
	add_link(instructions, *beg_branch_index);
	branch_location->val = instructions->length;
}

PDA *create_while_pda(Linked_List *instructions, Link *branch_location, int *beg_branch_index) {
	PDA *pda = malloc(sizeof(PDA));
	pda->data = calloc(sizeof(void*), 3);
	pda->data[0] = (void *) instructions;
	pda->data[1] = (void *) branch_location;
	pda->data[2] = (void *) beg_branch_index;
	pda->execute = &while_execute;
	return pda;
}

void function_execute(PDA *pda) {	
	Linked_List *instructions = (Linked_List *) pda->data[0];
	// Removes unnecessary POP_OPs
	for (int i = 0; i < *((int*) pda->data[2]); i++) {
			remove_last_link(instructions);
	}

	Link *branch_location = (Link *) pda->data[1];
	add_link(instructions, PUSH_OP);
	add_link(instructions, 0);
	add_link(instructions, RET_OP);
	branch_location->val = instructions->length;
}

PDA *create_func_pda(Linked_List *instructions, Link *branch_location, int *num_arg) {
	PDA *pda = malloc(sizeof(PDA));
	pda->data = calloc(sizeof(void*), 3);
	pda->data[0] = (void *) instructions;
	pda->data[1] = (void *) branch_location;
	pda->data[2] = (void *) num_arg;
	pda->execute = &function_execute;
	return pda;
}

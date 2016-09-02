#ifndef PDA_H
#define PDA_H

#include <stdlib.h>
#include "linked_list.h"
#include "compiler.h"

typedef struct PDA PDA;

struct PDA {
	void **data;
	void (*execute)(PDA *pda);
};

void if_execute(PDA *pda);
PDA *create_if_pda(Linked_List *instructions, Link *branch_location);

void function_execute(PDA *pda);
PDA *create_func_pda(Linked_List *instructions, Link *branch_location);

#endif // PDA_H

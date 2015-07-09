#include "Bytecode.h"

Operation new_op(char *name, int numOps) {
	Operation op;
	op.name = name;
	op.numOps = numOps;
	return op;
}

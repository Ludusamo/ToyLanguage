#include "Bytecode.h"

Operation new_op(const char *name, int numOps) {
	Operation op;
	op.name = name;
	op.numOps = numOps;
	return op;
}

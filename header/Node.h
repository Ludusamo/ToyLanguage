#ifndef NODE_H
#define NODE_H

#include "Statement.h"
#include <vector>

class Node {
protected:
	Statement masterStatement;
	virtual void execute(){};
};

#endif // NODE_H
